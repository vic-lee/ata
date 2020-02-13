#include <bitset>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    const int kMaxValue = 20000000;

    int ctr = 0;

    auto prime = bitset<kMaxValue>();

    prime.set();
    for (unsigned long n = 3; n * n < kMaxValue; n += 2) {
        if (prime[n / 2]) {
            ctr++;
            printf("n is %lu, %lu is prime, start from %lu, incr %lu\n", n,
                   (n / 2), n * n, n * 2);
            for (unsigned long index = n * n; index < kMaxValue;
                 index += n * 2) {
                prime[index / 2] = false;
            }
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds"
         << endl;

    cout << ctr << endl;
}