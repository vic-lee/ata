#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

// Maximum number of bits permitted by input
const int MAX_BITCOUNT = 50;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

bitset<MAX_BITCOUNT> min_desolate_num(UIN num_ones, UIN num_zeroes) {
    auto bs = bitset<MAX_BITCOUNT>();

    // maximum number of `101`s that can be used in the bitset
    int max_template_count = min(num_zeroes, num_ones / 2);
    int remaining_ones     = num_ones - max_template_count * 2;
    int remaining_zeroes   = num_zeroes - max_template_count;
    // number of 1s to set before prepending `101`s
    int right_padded_ones = remaining_ones;

    // if there are remaining zeroes, to maximize the number of ones next
    // to zeroes, place a `1` at the front of the binary.
    // note that due to the way `max_template_count` is defined,
    // either `remaining_ones` or `remaining_zeroes` will be 0 | 1
    // (otherwise we would've added another `101`).
    if (remaining_ones && remaining_zeroes) {
        right_padded_ones--;
    }

    size_t cur = 0;

    while (right_padded_ones > 0) {
        bs.set(cur++);
        right_padded_ones--;
        num_ones--;
    }

    // number of ones has to be decremented to zero.
    // number of zeroes need not be 0, because leading zeroes are allowed.
    while (num_ones > 0) {
        if (num_ones >= 2 && num_zeroes >= 1) {
            // prepend another `101`
            bs.set(cur++);
            bs.set(cur++, 0);
            bs.set(cur++);
            num_ones -= 2;
            num_zeroes--;
        } else {
            // use remaining ones. this branch should be executed once only.
            bs.set(cur++);
            num_ones--;
        }
    }

    return bs;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    UIN A, B;
    cin >> A >> B;
    cout << min_desolate_num(A, B).to_ullong() << endl;
}
