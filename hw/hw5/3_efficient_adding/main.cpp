#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ULL = unsigned long long;
using MinQueue = priority_queue<ULL, vector<ULL>, greater<ULL>>;

MinQueue read_in() {
    unsigned int cnt, x;
    cin >> cnt;
    MinQueue nums;
    for (size_t i = 0; i < cnt; i++) {
        cin >> x;
        nums.push(x);
    }
    return nums;
}

ULL efficient_add(MinQueue& nums) {
    ULL sum = 0;
    while (nums.size() >= 2) {
        ULL x = nums.top();
        nums.pop();
        ULL y = nums.top();
        nums.pop();
        sum += x + y;
        nums.push(x + y);
    }
    return sum;
}

int main() {
    auto nums = read_in();
    cout << efficient_add(nums) << endl;
}
