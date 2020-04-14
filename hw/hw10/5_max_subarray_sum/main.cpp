#include <climits>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;
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
    vector<int> nums;
};

Input read_in() {
    Input in;
    UIN   size;
    cin >> size;
    in.nums = vector<int>(size, 0);
    for (size_t i = 0; i < size; i++) cin >> in.nums[i];
    return in;
}

LL process(const Input& in) {
    LL curr_sum = 0, max_sum = LLONG_MIN;
    for (auto const& num : in.nums) {
        curr_sum = max((LL)num, curr_sum + num);
        max_sum  = max(max_sum, curr_sum);
    }
    return max_sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(in) << endl;
}
