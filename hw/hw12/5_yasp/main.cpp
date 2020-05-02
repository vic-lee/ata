#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
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
    cout << oss.str() << endl;
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

vector<UIN> read_in() {
    // read all ints from a string
    string s;
    getline(std::cin, s);
    istringstream iss(s);
    vector<UIN>   v((istream_iterator<UIN>(iss)), istream_iterator<UIN>());

    return v;
}

vector<UIN> process(vector<UIN>& nums) {
    vector<UIN> flips;
    vector<UIN> nums_copy  = nums;
    vector<UIN> _test_data = nums;

    // reverses `nums` from index 0 to `loc`, inclusive.
    auto flip = [&nums, &flips](size_t loc) {
        reverse(nums.begin(), nums.begin() + loc + 1);
        // because in the actual output the flip location starts counting from
        // the end of the array, actual output num is 'inverse' to `loc`.
        UIN flip_output = nums.size() - loc;
        flips.push_back(flip_output);
    };

    // filter out inputs that are either sorted or have a single element
    if (nums.size() == 1) {
        return flips;
    } else if (is_sorted(nums.begin(), nums.end())) {
        return flips;
    } else if (is_sorted(nums.begin(), nums.end(), greater<UIN>())) {
        flips.push_back(1);
        return flips;
    }

    size_t cur = 1;

    // invariants:
    //      subarray [0, cur) is sorted in ascending order (not inclusive)
    //      nums_copy the same as nums
    while (cur < nums.size()) {
        // attempts to transform nums[0, cur] into the descending order
        // of [0, cur], represented in `nums_copy`. once `nums` matches this
        // reverse order, do `flip(cur)` to transform it into ascending order
        sort(nums_copy.begin(), nums_copy.begin() + cur + 1, greater<UIN>());
        auto it =
            find(nums_copy.begin(), nums_copy.begin() + cur + 1, nums[cur]);
        // the index of the current element, in the descending subarr [0, cur].
        size_t target_loc = it - nums_copy.begin();

        if (target_loc == cur) {
            // nums[0, cur] in descending order.
            flip(cur - 1);
            flip(cur);
        } else if (target_loc == 0) {
            // nums[0, cur] already sorted, do nothing
        } else {
            flip(cur);
            flip(target_loc);
            flip(target_loc - 1);
            flip(cur);
        }

        nums_copy = nums;
        cur++;
    }

    return flips;
}

void fmtout(vector<UIN>& flips) {
    for (auto const f : flips) cout << f << ' ';
    cout << 0 << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = process(in);
    fmtout(out);
}
