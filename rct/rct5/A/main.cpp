#include <iostream>
#include <vector>

using namespace std;

void min_steps() {
    int sum = 0, N, x, count = 0;
    cin >> N;
    vector<size_t> zero_locs, nums(N, 0);

    for (size_t i = 0; i < N; ++i) {
        cin >> x;
        sum += x;
        nums[i] = x;
        if (x == 0)
            count++;
    }

    if (count != 0)
        sum += count;

    if (sum == 0)
        count++;

    cout << count << endl;
}

int main() {
    int test_cnt;
    cin >> test_cnt;
    for (int i = 0; i < test_cnt; ++i)
        min_steps();
}
