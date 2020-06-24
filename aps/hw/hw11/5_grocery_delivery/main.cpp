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

struct Output {
    string arrangements;
    size_t num_items;

    bool operator<(const Output& other) const {
        return num_items < other.num_items;
    }
};

Output arrange_boxes(ULL box1_cap, ULL box2_cap, size_t curr, string solution,
                     const vector<UIN>& volumes) {
    if (curr >= volumes.size()) return {solution, curr};
    auto curr_item_vol = volumes[curr];

    if (curr_item_vol <= box1_cap && curr_item_vol <= box2_cap) {
        return max(arrange_boxes(box1_cap - curr_item_vol, box2_cap, curr + 1,
                                 solution + "1st\n", volumes),
                   arrange_boxes(box1_cap, box2_cap - curr_item_vol, curr + 1,
                                 solution + "2nd\n", volumes));
    } else if (curr_item_vol <= box1_cap) {
        return arrange_boxes(box1_cap - curr_item_vol, box2_cap, curr + 1,
                             solution + "1st\n", volumes);
    } else if (curr_item_vol <= box2_cap) {
        return arrange_boxes(box1_cap, box2_cap - curr_item_vol, curr + 1,
                             solution + "2nd\n", volumes);
    }

    return {solution, curr};
}

void deliver_groceries(Input& in) {
    auto res =
        arrange_boxes(in.box_capacity, in.box_capacity, 0, "", in.volumes);

    cout << res.num_items << endl << res.arrangements;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    deliver_groceries(in);
}
