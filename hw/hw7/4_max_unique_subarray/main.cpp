#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using UIN = unsigned int;

vector<UIN> read_in() {
    UIN N, x;
    cin >> N;
    vector<UIN> nums(N, 0);
    for (UIN i = 0; i < N; i++) {
        cin >> x;
        nums[i] = x;
    }
    return nums;
}

UIN find_max_unique_subarray_len(const vector<UIN>& nums) {
    unordered_map<UIN, UIN> last_seen_at;
    UIN start = 0, end = 0, maxlen = 0;

    while (end < nums.size()) {
        auto cur = nums[end];
        if (last_seen_at.find(cur) == last_seen_at.end()) {
            last_seen_at[cur] = end;
        } else {
            maxlen = max(end - start, maxlen);
            start = max(last_seen_at[cur] + 1, start);
            last_seen_at[cur] = end;
        }
        end++;
    }

    return max(end - start, maxlen);
}

int main() {
    auto nums = read_in();
    cout << find_max_unique_subarray_len(nums) << endl;
}
