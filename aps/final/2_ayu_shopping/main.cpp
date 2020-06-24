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

/**
 * Given a budget and prices from a number of categories (a 2-D product matrix),
 * maximize budget usage while requiring purchase of one item per category.
 *
 * Reference:
 *  https://cs.nyu.edu/~joannakl/aps_s20/slides/11-dynamic_programming_2.html#15
 */
LL shop_candies(Input& in) {
    // Let `C` be the total number of categories.
    // `memo[m][i]` stores the maximum amount that can be spent under a budget
    // of `m`, using one item per category from categories [i ... C].
    auto memo = std::vector<std::vector<LL>>(
        in.budget + 1, std::vector<LL>(in.prices.size(), LLONG_MIN));

    /**
     * Return the maximum amount that can be spent within the limits of
     * `remaining_budget`, using products from `category` to the final category.
     *
     * Recurrence relation:
     *  ```
     * shop( -*, * ) = -INF
     * shop( m, C )  = M - m        // have purchased from all categories
     * shop( m, i )  = MAX( shop( m - k, i + 1 ) for k in prices[i] )
     *      // note: of all the choices available for category `i`, pick the
     *      // one that would result in maximum budget usage down the road
     *      // (remember: budget usage is exactly what `shop` would return)
     * ```
     */
    std::function<LL(int, int)> shop = [&](int remaining_budget, int category) {
        if (remaining_budget < 0) return LLONG_MIN;
        if (category == in.prices.size()) return in.budget - remaining_budget;

        if (memo[remaining_budget][category] != LLONG_MIN)
            return memo[remaining_budget][category];

        LL best = LLONG_MIN;
        for (int i = 0; i < in.prices[category].size(); i++) {
            best = max(best, shop(remaining_budget - in.prices[category][i],
                                  category + 1));
        }

        memo[remaining_budget][category] = best;

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
