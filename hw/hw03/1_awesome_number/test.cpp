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
    for (unsigned long n = 2; n * n < kMaxValue; ++n)
        if (prime[n]) {
            ctr++;
            for (unsigned long index = n * n; index < kMaxValue; index += n)
                prime[index] = false;
        }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds"
         << endl;
    cout << ctr << endl;
}