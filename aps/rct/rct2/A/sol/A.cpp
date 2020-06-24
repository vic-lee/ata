#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // handle case where n<=2.
    if (n % 2 == 1 || n <= 2) {
        cout << "NO";
    } else
        cout << "YES";
}