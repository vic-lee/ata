#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int pp = 1, p = 1;
    if (N == 1 || N == 2) {
        cout << p << endl;
    } else {
        for (int i = 3; i <= N; i++) {
            int next = p + pp;
            pp = p; p = next;
        }
        cout << p << endl;
    }
}