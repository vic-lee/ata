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

void read_in() {}

void calc() {}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned int N, x;
    cin >> N;
    for (size_t i = 0; i < N / 2 + 1; i++)
        cin >> x;
    cout << x << endl;
}
