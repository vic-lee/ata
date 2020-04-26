#include <iostream>
#include <sstream>
#include <vector>

#define YEARS_MAX 10000

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

struct CptrEntry {
    UIN yi;
    UIN ai;
    UIN bi;
};

vector<CptrEntry> read_in() {
    UIN num_computers;
    cin >> num_computers;
    vector<CptrEntry> computers(num_computers);

    for (size_t i = 0; i < num_computers; i++) {
        CptrEntry ce;
        cin >> ce.yi >> ce.ai >> ce.bi;
        computers[i] = ce;
    }

    return computers;
}

void process(vector<CptrEntry>& computers) {
    int                  years_it  = 0;
    bool                 not_valid = true;
    vector<vector<bool>> years(computers.size(),
                               vector<bool>(YEARS_MAX, false));

    for (size_t comp_it = 0; comp_it < computers.size(); comp_it++) {
        auto entry = computers[comp_it];
        for (size_t x = entry.yi, delta = entry.bi - entry.ai; x < YEARS_MAX;
             x += delta) {
            years[comp_it][x] = true;
        }
    }

    while (years_it < YEARS_MAX) {
        not_valid = true;

        for (size_t comp_it = 0; comp_it < computers.size(); comp_it++) {
            if (!years[comp_it][years_it]) {
                not_valid = false;
                break;
            }
        }

        if (not_valid) {
            break;
        } else {
            years_it++;
        }
    }

    cout << (years_it < YEARS_MAX ? years_it : -1) << endl;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
    fmtout();
}
