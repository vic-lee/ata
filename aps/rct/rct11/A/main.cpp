#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Input {
    int         N;
    int         D;
    vector<int> gems;
};

Input read_in() {
    Input in;
    cin >> in.N >> in.D;
    in.gems = vector<int>(in.N, 0);
    for (size_t i = 0; i < in.N; i++) cin >> in.gems[i];
    return in;
}

void process(Input& in) {}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
    fmtout();
}
