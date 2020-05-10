#include <iomanip>
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

ULL count_ways_to_change(int target) {
    const vector<int> COIN_VALS = {5,   10,   20,   50,   100,  200,
                                   500, 1000, 2000, 5000, 10000};

    vector<ULL> memo(target + 1, 0);

    memo[0] = 1;
    for (int i = 0; i < COIN_VALS.size(); i++) {
        for (int j = COIN_VALS[i]; j <= target; j++) {
            memo[j] += memo[j - COIN_VALS[i]];
        }
    }

    return memo[target];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    // READ INPUT
    string line;
    getline(cin, line);
    auto dot_pos = line.find_first_of('.');

    // target sum: 0.00 < target <= 300.00
    int target_cents =
        100 * stoi(line.substr(0, dot_pos)) + stoi(line.substr(dot_pos + 1));

    auto ways = count_ways_to_change(target_cents);
    cout << right << setw(6) << line << right << setw(17) << ways << endl;
}
