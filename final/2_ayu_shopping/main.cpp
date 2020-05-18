#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using ULL = unsigned long long;

#define FOR_N(n) for (int i = 0; i < n; i++)

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Input {
    std::vector<std::vector<UIN>> prices;
    LL                            budget;
    bool                          has_solution;

    Input(LL budget, UIN num_categories) : budget(budget), has_solution(true) {
        prices = std::vector<std::vector<UIN>>(num_categories);
    }
};

Input read_in() {
    LL  budget;
    UIN num_categories;
    cin >> budget >> num_categories;

    std::vector<UIN> min_prices(num_categories, UINT_MAX);
    Input            in(budget, num_categories);

    UIN num_flavors;
    FOR_N(num_categories) {
        cin >> num_flavors;
        in.prices[i] = std::vector<UIN>(num_flavors, UINT_MAX);
        for (size_t j = 0; j < num_flavors; j++) {
            cin >> in.prices[i][j];
            min_prices[i] = min(min_prices[i], in.prices[i][j]);
        }
    }

    auto min_required_cost =
        accumulate(min_prices.begin(), min_prices.end(), 0);

    in.has_solution = min_required_cost <= budget;

    return in;
}

LL shop_candies(Input& in) {
    auto memo = std::vector<std::vector<LL>>(
        in.budget + 1, std::vector<LL>(in.prices.size(), LLONG_MIN));

    std::function<long long(int, int)> shop = [&](int remaining_budget,
                                                  int category) {
        if (remaining_budget < 0) return LLONG_MIN;
        if (category == in.prices.size()) return in.budget - remaining_budget;

        if (memo[remaining_budget][category] != LLONG_MIN)
            return memo[remaining_budget][category];

        LL best = LLONG_MIN;
        for (int i = 0; i < in.prices[category].size(); i++) {
            best = max(best, shop(remaining_budget - in.prices[category][i],
                                  category + 1));
        }

        return best;
    };

    return shop(in.budget, 0);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    if (!in.has_solution) {
        cout << "no solution" << endl;
        return 0;
    }

    cout << shop_candies(in) << endl;
}
