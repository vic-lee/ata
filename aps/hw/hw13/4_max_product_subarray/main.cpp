#include <algorithm>
#include <deque>
#include <iostream>
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
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

class BigInt {
    deque<int> digits_;
    bool       positive_;

   public:
    BigInt(string str_num) {
        if (str_num[0] == '-') {
            positive_ = false;
            digits_   = deque<int>(str_num.size() - 1);
            for (size_t i = 1; i < str_num.size(); i++) {
                digits_[i] = str_num[i];
            }
        } else {
            positive_ = true;
            digits_   = deque<int>(str_num.begin(), str_num.end());
        }
    }

    BigInt(LL num) {
        positive_ = num < 0;
        num       = abs(num);
        while (num) {
            digits_.push_back(num % 10);
            num /= 10;
        }
    }

    BigInt(vector<int> digits, bool is_positive)
        : digits_(digits.begin(), digits.end()), positive_(is_positive) {}

    char operator[](size_t i) const { return digits_[i]; }

    bool is_positive() const { return positive_; }

    size_t size() const { return digits_.size(); }

    friend ostream& operator<<(ostream& os, const BigInt& number);

    bool operator<(const BigInt& other) {
        if (size() != other.size()) {
            return size() < other.size();
        }
        for (size_t i = 0; i < size(); i++) {
            if (digits_[i] != other[i]) {
                return digits_[i] < other[i];
            }
        }
        return false;
    }

    BigInt operator*(const BigInt& other) {
        // Guard against invalid inputs w/ no digits
        if (other.size() == 0 || size() == 0) {
            return BigInt("0");
        }

        vector<int> result(size() + other.size(), 0);
        int         it_self = 0, it_other = 0;
        for (int i = size() - 1; i >= 0; i--) {
            int carry  = 0;
            int d_self = digits_[i] - '0';

            it_other = 0;

            for (int j = other.size() - 1; j >= 0; j--) {
                int d_other = other[j] - '0';
                int sum = d_self * d_other + result[it_self + it_other] + carry;

                // cout << "sum: " << sum << "\td_self: " << d_self
                //  << "\td_other: " << d_other << endl;

                carry                      = sum / 10;
                result[it_self + it_other] = sum % 10;

                // print_iterable(result);

                it_other++;
            }

            if (carry > 0) {
                result[it_self + it_other] += carry;
            }

            it_self++;
        }

        auto back_begin = find_if_not(result.rbegin(), result.rend(),
                                      [](const char& d) { return d == 0; });

        auto back_begin_idx = distance(begin(result), back_begin.base()) - 1;
        if (back_begin_idx + 1 < result.size()) {
            result.erase(result.begin() + back_begin_idx + 1, result.end());
        }
        reverse(back_begin, result.rend());

        bool is_res_positive = (positive_ && other.is_positive()) ||
                               (!positive_ && !other.is_positive());

        BigInt res(move(result), is_res_positive);
        return res;
    }
};

ostream& operator<<(ostream& os, const BigInt& number) {
    if (!number.positive_) {
        os << '-';
    }
    for (auto const d : number.digits_) {
        os << d;
    }
    return os;
}

using Input = vector<BigInt>;

Input read_in() {
    UIN num_sz;  // 1 <= N <= 100

    cin >> num_sz;
    Input nums(num_sz, 0);

    int tmp;
    for (size_t i = 0; i < num_sz; i++) {
        cin >> tmp;
        nums[i] = BigInt(tmp);
    }

    return nums;
}

BigInt max_product_subarray(Input& nums) {
    // The maximum product found up to the current iteration
    BigInt max_product = nums[0];
    // The minimum achievable product of subarr [x ... i]
    BigInt cur_min = nums[0];
    // The maximum achievable product of subarr [x ... i]
    BigInt cur_max = nums[0];

    for (size_t i = 1; i < nums.size(); i++) {
        auto num = nums[i];

        if (num < 0) {
            // If the current number is negative, then multiplying `num`
            // with the previously *largest* product (product up to i - 1)
            // would yield the current min. Hence the swap.
            swap(cur_max, cur_min);
        }

        // Continue multiplying in the currently selected subarray, or
        // begin a new subarray sequence, depending on which one is smaller
        // or bigger. Finally, keep track of the maximum product.

        cur_min     = min(num, cur_min * num);
        cur_max     = max(num, cur_max * num);
        max_product = max(cur_max, max_product);

        cout << cur_min << " " << cur_max << endl;

        // cout << cur_min << " " << cur_max << " " << max_product << endl;
    }

    return max_product;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << max_product_subarray(in) << endl;
}
