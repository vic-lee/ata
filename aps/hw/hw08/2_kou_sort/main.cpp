#include <iostream>
#include <sstream>

#define MAX_SZ 500000

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const &item : items) {
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

ULL _merge(int *nums, size_t L, size_t R, size_t M) {
    size_t i = L, j = M + 1, k = L;
    int buf[MAX_SZ];
    ULL inv_cnt = 0;

    while (i <= M && j <= R) {
        if (nums[i] <= nums[j]) {
            buf[k++] = nums[i++];
        } else {
            buf[k++] = nums[j++];
            inv_cnt += M - i + 1;
        }
    }

    while (i <= M) buf[k++] = nums[i++];
    while (j <= R) buf[k++] = nums[j++];

    for (i = L; i < k; i++) nums[i] = buf[i];

    return inv_cnt;
}

ULL _mergesort(int *nums, size_t L, size_t R) {
    ULL inv_cnt = 0;
    if (L < R) {
        int M = (L + R) / 2;
        inv_cnt += _mergesort(nums, L, M);
        inv_cnt += _mergesort(nums, M + 1, R);
        inv_cnt += _merge(nums, L, R, M);
    }
    return inv_cnt;
}

ULL count_inversions(int *nums, int sz) { return _mergesort(nums, 0, sz - 1); }

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nums[MAX_SZ];

    UIN nums_sz;
    scanf("%u\n", &nums_sz);
    for (size_t i = 0; i < nums_sz; i++) scanf("%u\n", &nums[i]);

    cout << count_inversions(nums, nums_sz) << endl;
}
