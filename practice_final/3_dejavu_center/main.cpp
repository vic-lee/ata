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
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

vector<int> sieve(int n) {
    vector<int>  primes   = {};
    const int    max_size = n + 1;
    vector<bool> is_prime(max_size, true);

    is_prime[0] = false;
    is_prime[2] = true;
    is_prime[3] = true;

    for (size_t p = 3; p * p <= max_size; p += 2) {
        if (is_prime[p]) {
            for (int i = p * p; i < max_size; i += p) {
                is_prime[i] = false;
            }
        }
    }

    for (size_t i = 0; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            if (i == 2 || (i % 2 != 0)) primes.push_back(i);
        }
    }

    // print_iterable(primes);

    return primes;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, C;
    cin >> N >> C;

    auto nums = sieve(N);

    size_t start, end;

    if (nums.size() % 2 == 0 && 2 * C <= nums.size()) {
        start = (nums.size() - 2 * C) / 2;
        end   = start + 2 * C;
    } else if (nums.size() % 2 != 0 && (2 * C - 1) <= nums.size()) {
        start = (nums.size() - (2 * C - 1)) / 2;
        end   = start + 2 * C - 1;
    } else {
        start = 0;
        end   = nums.size();
    }

    cout << N << ' ' << C << ':';
    for (size_t i = start; i < end; i++) {
        cout << ' ' << nums[i];
    }
    cout << endl;
}
