#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Input {
    vector<UIN> volumes;
    UIN         box_capacity;
};

struct BoxCapacities {
    UIN box1;
    UIN box2;
};

Input read_in() {
    Input in;
    UIN   item_count;
    cin >> item_count >> in.box_capacity;
    in.volumes = vector<UIN>(item_count, 0);

    for (size_t i = 0; i < item_count; i++) {
        cin >> in.volumes[i];
    }

    return in;
}

void process(Input& in) {
    auto                                 volume_it = in.volumes.begin() + 1;
    unordered_map<string, BoxCapacities> prev, curr;
    if (in.volumes[0] > in.box_capacity) {
        cout << 0 << endl;
        return;
    }

    // store the 1st elem in the 1st box, by default
    curr["1st\n"] = {in.box_capacity - in.volumes[0], in.box_capacity};

    do {
        prev = curr;
        curr.clear();
        auto curr_item_vol = *volume_it;

        for (auto prevmap_it = prev.begin(); prevmap_it != prev.end();
             prevmap_it++) {
            auto remaining_capacities = prevmap_it->second;
            auto res_str              = prevmap_it->first;

            // cout << remaining_capacities.box1 << " "
            //      << remaining_capacities.box2 << " " << curr_item_vol << " "
            //      << res_str;

            // ignore this entry if no box can fit the current item
            if (curr_item_vol > remaining_capacities.box1 &&
                curr_item_vol > remaining_capacities.box2) {
                // cout << "ignoring " << res_str;
                continue;
            }

            if (curr_item_vol <= remaining_capacities.box1) {
                auto next_res_str = res_str + "1st\n";
                if (prev.find(next_res_str) == prev.end()) {
                    curr[next_res_str] = {
                        remaining_capacities.box1 - curr_item_vol,
                        remaining_capacities.box2};
                    // cout << "created entry:\n" << next_res_str;
                } else {
                    curr[next_res_str] = prev[next_res_str];
                }
            }

            if (curr_item_vol <= remaining_capacities.box2) {
                auto next_res_str = res_str + "2nd\n";
                if (prev.find(next_res_str) == prev.end()) {
                    curr[next_res_str] = {
                        remaining_capacities.box1,
                        remaining_capacities.box2 - curr_item_vol};
                    // cout << "created entry:\n" << next_res_str;
                } else {
                    curr[next_res_str] = prev[next_res_str];
                }
            }
        }

        volume_it++;
    } while (!curr.empty() && volume_it != in.volumes.end());

    auto box_arrangements =
        curr.empty() ? prev.begin()->first : curr.begin()->first;
    auto box_caps  = curr.empty() ? prev.begin()->second : curr.begin()->second;
    auto num_boxes = distance(in.volumes.begin(), volume_it) - 1;

    cout << num_boxes << endl << box_arrangements;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
