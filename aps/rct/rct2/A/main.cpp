#include <iostream>

using namespace std;

int main() {
    int in;
    cin >> in;

    if (in == 0 || in == 2) {
        cout << "NO" << endl;
    } else if (in % 2 != 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}