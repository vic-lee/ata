#include <limits.h>

#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

const long BS_SIZE = 10000001;

struct PrimePair {
    long front;
    long back;

    PrimePair(long ft, long bk) : front(ft), back(bk) {}
    PrimePair() : front(LONG_MAX), back(LONG_MAX) {}
};

struct Output {
    PrimePair min_pair;
    PrimePair max_pair;

    Output() : min_pair(), max_pair() {}
};

bool is_prime_pair_defined(PrimePair pp) {
    return pp.front != LONG_MAX && pp.back != LONG_MAX;
}

bool is_output_defined(Output out) {
    return (is_prime_pair_defined(out.min_pair) &&
            is_prime_pair_defined(out.max_pair));
}

inline void set_1(bitset<BS_SIZE>& bs, long k) { bs.set(k, 1); }

inline void set_0(bitset<BS_SIZE>& bs, long k) { bs.set(k, 0); }

long min_odd_divisor(long floor, long div) {
    long      r   = (floor + div) % div;
    const int ans = r == 0 ? floor : floor + div - r;
    return ans % 2 == 0 ? ans + div : ans;
}

long find_prime_gaps(long start, long end) {
    long   prev_prime = LONG_MAX, curr_prime = LONG_MAX;
    Output out;

    const long                primebase_max = ceil(sqrt(end));
    const long                bs_range      = end - start;
    auto                      primebase     = vector<bool>(primebase_max, true);
    unordered_map<long, long> primegap_counts;
    // handle special prime cases
    primebase[0] = false;
    primebase[1] = false;

    auto bs = bitset<BS_SIZE>();
    bs.set();

    if (start == 1) set_0(bs, 0);  // handle 1 is not prime

    // initialize prime number designations
    for (long k = 3; k <= primebase_max; k += 2) {
        if (primebase[k]) {
            for (long c = k * k, d = k << 1; c <= primebase_max; c += d)
                primebase[c] = false;
            for (long c = min_odd_divisor(start, k), d = k << 1; c <= end;
                 c += d) {
                if (c != k) {
                    set_0(bs, c - start);
                }
            }
        }
    }

    if (start <= 2) curr_prime = 2;

    long gap_count_max     = LONG_MIN;
    long mode              = LONG_MIN;
    long mode_entry_counts = 0;
    for (long k = (start % 2 == 0) ? start + 1 : start; k <= end; k += 2) {
        if (bs.test(k - start)) {
            prev_prime = curr_prime;
            curr_prime = k;
            if (prev_prime != LONG_MAX && curr_prime != LONG_MAX) {
                long curr_gap = curr_prime - prev_prime;
                primegap_counts[curr_gap]++;
                if (primegap_counts[curr_gap] > gap_count_max) {
                    gap_count_max     = primegap_counts[curr_gap];
                    mode              = curr_gap;
                    mode_entry_counts = 1;
                } else if (primegap_counts[curr_gap] == gap_count_max) {
                    mode_entry_counts++;
                }
            }
        }
    }

    return mode_entry_counts != 1 ? -1 : mode;
}

int main() {
    long a, b;
    cin >> a >> b;
    if (a == b) {
        printf("-1\n");
        return 0;
    }
    cout << find_prime_gaps(a, b) << endl;
}
