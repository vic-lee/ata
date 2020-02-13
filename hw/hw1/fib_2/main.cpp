#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    long pp = 0, p = 1;

    if (N == 1) {
        cout << 0 << endl;
    } else if (N == 2) {
        cout << 1 << endl;
    } else {
        for (int i = 3; i <= N; i++) {
            long next = p + pp;
            pp = p; p = next;
        }
        cout << p << endl;
    }
}