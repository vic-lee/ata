#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

int main() {
    unsigned int in_sze, x, curr = 0;
    unsigned long long sum = 0, vct_total = 0;
    cin >> in_sze;

    if (in_sze == 1) {
        cin >> x;
        cout << x << endl;
        return 0;
    }

    deque<int> nums(in_sze, 0);

    for (unsigned int i = 0; i < in_sze; ++i) {
        cin >> x;
        nums[i] = x;
    }

    sort(nums.begin(), nums.end());

    for (unsigned int i = 0; i < nums.size(); ++i) {
        vct_total += nums[i];
    }

    sum = vct_total;
    while (vct_total > nums.back()) {
        vct_total -= nums[curr];
        sum = sum + vct_total + nums[curr];
        curr++;
    }

    cout << sum << endl;
}
