#include <math.h>
#include <bitset>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

const int MAX_IN = 20000001;

inline void set_1(bitset<MAX_IN>& bs, int k) {
    bs.set(k, 1);
}

inline void set_0(bitset<MAX_IN>& bs, int k) {
    bs.set(k, 0);
}

int count_awesome(int max_prime) {
    int awesome_ctr = 0;
    auto bs = bitset<MAX_IN>();
    bs.set();

    set_0(bs, 0);
    set_0(bs, 1);

    // iterate 3 ... sqrt(n)
    for (int k = 3; k * k <= max_prime; k += 2) {
        // printf("Testing %d: %d\n", k, bs.test(k));
        if (bs.test(k)) {
            for (int c = k * k; c <= max_prime; c += 2 * k)
                set_0(bs, c);
            if (k % 10 == 1)
                awesome_ctr++;
        }
    }

    int it = (int)sqrt(max_prime);
    while (it % 10 != 1)
        ++it;
    // iterate sqrt(n) ... n
    for (; it <= max_prime; it += 10) {
        // printf("Testing %d: %d\n", it, bs.test(it));
        if (bs.test(it))
            awesome_ctr++;
    }

    return awesome_ctr;
}

int main() {
    int in;
    cin >> in;

    auto start = high_resolution_clock::now();

    cout << count_awesome(in) << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds"
         << endl;
}
