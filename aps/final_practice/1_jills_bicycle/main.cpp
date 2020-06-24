#include <climits>
#include <iostream>
#include <sstream>
#include <vector>

#define FOR_N(n) for (int i = 0; i < n; i++)

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

std::vector<int> read_in() {
    UIN num_count;
    std::cin >> num_count;
    auto safety_vals = std::vector<int>(num_count, INT_MIN);

    FOR_N(num_count) { cin >> safety_vals[i]; }

    return safety_vals;
}

LL max_subarr(const std::vector<int>& safety_vals) {
    // LL              res = 0;
    // std::vector<LL> memo(safety_vals.size(), LLONG_MIN);

    // memo[0] = max(safety_vals[0], 0);
    // res     = memo[0];
    // for (size_t i = 1; i < safety_vals.size(); i++) {
    //     memo[i] = max((long long)safety_vals[i], memo[i - 1] +
    //     safety_vals[i]); memo[i] = max(memo[i], (long long)0); res     =
    //     max(res, memo[i]);
    // }

    // return res;

    int res = INT_MIN, local_max = 0;

    for (int i = 0; i < safety_vals.size(); i++) {
        local_max = local_max + safety_vals[i];
        if (res < local_max) res = local_max;
        if (local_max < 0) local_max = 0;
    }

    return res;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = max_subarr(in);

    if (out > 0) {
        cout << out << endl;
    } else {
        cout << "No safe streets along this route." << endl;
    }
}
