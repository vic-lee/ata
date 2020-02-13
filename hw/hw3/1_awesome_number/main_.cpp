#include <math.h>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

int main() {
    int N, awesomeCtr = 0;
    cin >> N;

    auto start = high_resolution_clock::now();

    vector<bool> primemap(2 * N + 2, true);

    primemap[0] = false;
    primemap[1] = false;

    for (int i = 3; i * i <= N * 2; i += 2) {
        if (primemap[i / 2]) {
            for (int n = i * i; n <= N; n += i * 2) {
                primemap[n / 2] = false;
            }

            if (i % 10 == 1) {
                awesomeCtr++;
            }
        }
    }

    int c = (int)sqrt(N);
    while (c % 10 != 1)
        c++;

    for (int i = c; i <= N * 2; i += 10) {
        if (primemap[i / 2]) {
            awesomeCtr++;
        }
    }

    printf("%d\n", awesomeCtr);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds"
         << endl;
}