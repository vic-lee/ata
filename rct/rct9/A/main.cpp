#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    UIN n;
    cin >> n;
    UIN big   = (UIN)pow(n, 2);
    UIN small = 1;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n / 2) - 1; j++) {
            cout << small++ << " " << big-- << " ";
        }
        cout << small++ << " " << big-- << "\n";
    }
}
