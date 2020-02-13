#include <math.h>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

enum PrimeTypes {
    NotPrime,
    ProbablyPrime,
    IsPrime,
};

int main() {
    int N, awesomeCtr = 0;
    cin >> N;

    auto start = high_resolution_clock::now();

    vector<PrimeTypes> primemap(N + 1, ProbablyPrime);

    primemap[0] = NotPrime;
    primemap[1] = NotPrime;

    for (int i = 3; i * i <= N; i += 2) {
        if (primemap[i] == ProbablyPrime) {
            primemap[i] = IsPrime;

            for (int c = i * i; c <= N; c += i * 2) {
                primemap[c] = NotPrime;
            }

            if (i % 10 == 1) {
                awesomeCtr++;
            }
        }
    }

    int c = (int)sqrt(N);
    while (c % 10 != 1)
        c++;

    for (int i = c; i <= N; i += 10) {
        if (primemap[i] == ProbablyPrime) {
            awesomeCtr++;
        }
    }

    printf("%d\n", awesomeCtr);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds"
         << endl;
}