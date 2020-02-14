#include <limits.h>
#include <bitset>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

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

inline void set_1(bitset<BS_SIZE>& bs, long k) {
    bs.set(k, 1);
}

inline void set_0(bitset<BS_SIZE>& bs, long k) {
    bs.set(k, 0);
}

long min_odd_divisor(long floor, long div) {
    long r = (floor + div) % div;
    const int ans = r == 0 ? floor : floor + div - r;
    return ans % 2 == 0 ? ans + div : ans;
}

Output find_prime_gaps(long start, long end) {
    long min_gap = INT_MAX, max_gap = 0;
    long prev_prime = LONG_MAX, curr_prime = LONG_MAX;
    Output out;

    const long primebase_max = ceil(sqrt(end));
    const long bs_range = end - start;
    auto primebase = vector<bool>(primebase_max, true);
    // handle special prime cases
    primebase[0] = false;
    primebase[1] = false;

    auto bs = bitset<BS_SIZE>();
    bs.set();

    if (start == 1)
        set_0(bs, 0);  // handle 1 is not prime

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

    if (start <= 2)
        curr_prime = 2;

    // find min and max prime gaps
    for (long k = (start % 2 == 0) ? start + 1 : start; k <= end; k += 2) {
        if (bs.test(k - start)) {
            prev_prime = curr_prime;
            curr_prime = k;
            if (prev_prime != LONG_MAX && curr_prime != LONG_MAX) {
                long curr_gap = curr_prime - prev_prime;
                if (curr_gap < min_gap) {
                    min_gap = curr_gap;
                    out.min_pair = PrimePair(prev_prime, curr_prime);
                }
                if (curr_gap > max_gap) {
                    max_gap = curr_gap;
                    out.max_pair = PrimePair(prev_prime, curr_prime);
                }
            }
        }
    }

    return out;
}

void fmtout(Output out) {
    if (is_output_defined(out)) {
        printf("%ld %ld %ld %ld\n", out.min_pair.front, out.min_pair.back,
               out.max_pair.front, out.max_pair.back);
    } else {
        printf("-1\n");
    }
}

int main() {
    long a, b;
    cin >> a >> b;
    if (a == b) {
        printf("-1\n");
        return 0;
    }
    auto out = find_prime_gaps(a, b);
    fmtout(out);
}
