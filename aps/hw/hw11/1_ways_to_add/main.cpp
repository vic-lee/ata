#include <iostream>
#include <sstream>
#include <vector>

#define MODULO_CONST 1000000007

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using LD  = long double;
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
    // 1 <= N <= 100
    UIN N;
    // 1 <= K <= 100
    UIN K;
};

Input read_in() {
    Input in;
    cin >> in.N >> in.K;
    return in;
}

/**
 * Recurrence relations
 * ways(N, 1) = 1
 * ways(N, K) = sum(ways(N - X, K - 1) for X in 0 ... N inclusive)
 *
 * Reference:
 * https://cs.nyu.edu/~joannakl/aps_s20/slides/11-dynamic_programming_3.html#23
 */
ULL count_ways_to_add(vector<vector<LD>>& memo, UIN N, UIN K) {
    if (K == 1) {
        return 1;
    } else if (memo[N][K] != 0) {
        return memo[N][K];
    } else {
        ULL sum = 0;

        for (size_t x = 0; x <= N; x++) {
            auto next_N = N - x;
            auto next_K = K - 1;

            if (memo[next_N][next_K] == 0) {
                auto resp            = count_ways_to_add(memo, next_N, next_K);
                memo[next_N][next_K] = resp;
            }

            sum += memo[next_N][next_K];
            sum %= MODULO_CONST;
        }

        memo[N][K] = sum;
        return memo[N][K];
    }
}

void process(const Input& in) {
    vector<vector<LD>> memo(in.N + 1, vector<LD>(in.K + 1, 0.0));
    cout << count_ways_to_add(memo, in.N, in.K) << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
