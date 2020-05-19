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
    UIN nums[100001];
    UIN nums_count;
    UIN target_partitions_cnt;
};

Input read_in() {
    Input in;

    cin >> in.nums_count >> in.target_partitions_cnt;
    for (size_t i = 0; i < in.nums_count; i++) cin >> in.nums[i];

    return in;
}

ULL process(const Input& in) {
    const auto is_feasible_sum = [&in](ULL target) -> bool {
        UIN partitions_cnt    = 1;
        ULL curr_subarray_sum = 0;

        for (size_t i = 0; i < in.nums_count; i++) {
            if (in.nums[i] > target) {
                return false;
            } else {
                curr_subarray_sum += in.nums[i];

                if (curr_subarray_sum > target) {
                    partitions_cnt++;
                    curr_subarray_sum = in.nums[i];
                }
            }
        }

        return partitions_cnt <= in.target_partitions_cnt;
    };

    ULL lowerbound = 1, upperbound = 0;
    ULL max_subarray_sum = 0, potential_sum;

    for (size_t i = 0; i < in.nums_count; i++) upperbound += in.nums[i];

    if (in.target_partitions_cnt == 1) return upperbound;

    while (lowerbound <= upperbound) {
        potential_sum = (lowerbound + upperbound) / 2;

        if (is_feasible_sum(potential_sum)) {
            max_subarray_sum = potential_sum;
            upperbound       = potential_sum - 1;
        } else {
            lowerbound = potential_sum + 1;
        }
    }

    return max_subarray_sum;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(in) << endl;
}
