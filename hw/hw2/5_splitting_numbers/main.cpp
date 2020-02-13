#include <cmath>
#include <iostream>

using namespace std;

struct SplitResponse {
    int a;
    int b;
};

SplitResponse split(const int in) {
    SplitResponse r; r.a = 0; r.b = 0;

    int n = in;
    bool isA = true;
    int exp = 0;

    while (n > 0) {
        int x = n & 0x1;
        if (x == 1) {
            if (isA) {
                r.a += pow(2, exp);
            } else {
                r.b += pow(2, exp);
            }
            isA = !isA;
        }
        exp++;
        n = n >> 1;
    }

    return r;
}

int main() {
    int n; cin >> n;
    SplitResponse r = split(n);
    printf("%d %d\n", r.a, r.b);
}