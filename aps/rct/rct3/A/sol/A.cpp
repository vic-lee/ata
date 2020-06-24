#include <iostream>

using namespace std;

bool isLucky(int n) {
    while (n) {
        int y = n % 10;
        if (y == 4 || y == 7) {
            n /= 10;
        } else
            return 0;
    }
    return 1;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        if (isLucky(i)) {
            if (n % i == 0) {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}