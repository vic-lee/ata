#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Input {
    UIN cap;
    vector<int> nums;
};

Input read_in() {
    Input in;
    UIN capacity, N, x;
    cin >> in.cap >> N;
    vector<int> nums(N, 0);
    for (size_t i = 0; i < N; i++) {
        cin >> x;
        nums[i] = x;
    }
    in.nums = nums;
    return in;
}

int knapsack(int target, vector<int> nums, int curr) {
    if (curr == -1 || target == 0)
        return 0;

    if (nums[curr] > target) {
        return knapsack(target, nums, curr - 1);
    }

    return max(nums[curr] + knapsack(target - nums[curr], nums, curr - 1),
               knapsack(target, nums, curr - 1));
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << knapsack(in.cap, in.nums, in.nums.size() - 1) << endl;
}
