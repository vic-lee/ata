#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << ' ';
    }
    oss << endl;
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
    vector<UIN> task_durations;
    UIN         num_nodes;
};

Input read_in() {
    Input in;
    UIN   num_tasks;
    cin >> num_tasks >> in.num_nodes;
    in.task_durations = vector<UIN>(num_tasks, 0);

    for (size_t i = 0; i < num_tasks; i++) cin >> in.task_durations[i];

    return in;
}

struct Cuts {
    vector<UIN> cuts;
    bool        is_valid;
};

Cuts has_cuts(const vector<UIN>& task_durations, long target, UIN num_nodes) {
    vector<UIN> cuts(num_nodes, 0);
    long        count = 0, sum = 0, cuts_idx = 0;

    for (int i = task_durations.size() - 1; i >= 0; i--) {
        if (task_durations[i] > target) return {cuts, false};

        sum += task_durations[i];
        if (sum > target) {
            count++;
            if (count <= num_nodes) {
                cuts[cuts_idx] = i + 1;
                cuts_idx++;
            }
            sum = task_durations[i];
        }
    }

    count++;
    return {cuts, count <= num_nodes};
}

Cuts find_cuts(const vector<UIN>& task_durations, long beg, long end,
               UIN num_nodes) {
    long mid = (beg + end) / 2;

    if (beg >= end) {
        return has_cuts(task_durations, end, num_nodes);
    } else {
        if (has_cuts(task_durations, mid, num_nodes).is_valid) {
            return find_cuts(task_durations, beg, mid, num_nodes);
        } else {
            return find_cuts(task_durations, mid + 1, end, num_nodes);
        }
    }
}

vector<UIN> process(const Input& in) {
    auto min = *min_element(in.task_durations.begin(), in.task_durations.end());
    UIN sum = accumulate(in.task_durations.begin(), in.task_durations.end(), 0);

    return find_cuts(in.task_durations, min, sum, in.num_nodes).cuts;
}

void fmtout(Input& in, vector<UIN>& cuts) {
    bool has_begin_cut = false;
    for (int i = in.num_nodes - 2; i >= 0; i--) {
        if (has_begin_cut || cuts[i] == 0) {
            has_begin_cut = true;
            cuts[i]       = max(cuts[i + 1] + 1, cuts[i]);
        }
    }

    int cuts_idx = in.num_nodes - 2;

    ostringstream oss;
    for (int i = 0; i < in.task_durations.size(); i++) {
        oss << in.task_durations[i] << ' ';
        if (cuts_idx >= 0 && i + 1 == cuts[cuts_idx]) {
            oss << "/ ";
            cuts_idx--;
        }
    }

    auto outstr = oss.str();
    // trim right whitespace
    outstr.erase(outstr.find_last_not_of(' ') + 1);
    cout << outstr << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in   = read_in();
    auto cuts = process(in);
    fmtout(in, cuts);
}
