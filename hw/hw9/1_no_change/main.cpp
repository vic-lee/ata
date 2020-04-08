#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using UIN           = unsigned int;
using CoinsCountMap = unordered_map<UIN, UIN>;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Input {
    UIN           target_amt;
    UIN           total_coin_val = 0;
    CoinsCountMap coins_map;
};

struct Output {
    UIN amt_paid;
    UIN coins_cnt;
};

Input read_in() {
    Input in;
    UIN   num_coins, x;
    cin >> in.target_amt >> num_coins;

    for (size_t i = 0; i < num_coins; i++) {
        cin >> x;
        in.coins_map[x]++;
        in.total_coin_val += x;
    }

    return in;
}

Output process(const Input& in) {
    struct MemoEntry {
        UIN           num_coins;
        int           exceeded;
        CoinsCountMap remaining_coins;
    };

    Output            out;
    vector<MemoEntry> memo(in.target_amt + 1,
                           {101, (int)in.total_coin_val, {}});

    for (size_t target = 0; target <= in.target_amt; target++) {
        auto use_entry = [&memo, &target](UIN prev_target, UIN coin_val) {
            memo[target] = {
                memo[prev_target].num_coins + 1,
                memo[prev_target].exceeded,
                memo[prev_target].remaining_coins,
            };
            /** remaining_coins[coin_val] guaranteed to be positive. */
            memo[target].remaining_coins[coin_val]--;
        };

        for (auto const& coin : in.coins_map) {
            auto const coin_val = coin.first;

            if (coin_val >= target) {
                int rest = target - coin_val;
                if (-rest <= memo[target].exceeded) {
                    /** Only use this coin if it at least matches the previous
                     * optimal exceed amount. If the new exceed amount is lower
                     * or equal to the previous one, using one coin is
                     * guaranteed to perform at least as good as the previous
                     * solution, since it only uses one coin.
                     */
                    memo[target] = {1, -rest, in.coins_map};
                    memo[target].remaining_coins[coin_val]--;
                }
            } else { /** the coin is lower than target value, check memo. */
                UIN remaining_target = target - coin_val;
                if (memo[remaining_target].remaining_coins[coin_val] == 0) {
                    /** this coin is not part of a valid solution, because
                     * all coins of this demonimation have been depleted. */
                    continue;
                }
                if (memo[remaining_target].exceeded < memo[target].exceeded) {
                    /** found a new optimal exceed value */
                    use_entry(remaining_target, coin_val);
                } else if (memo[remaining_target].exceeded ==
                           memo[target].exceeded) {
                    if (memo[remaining_target].num_coins + 1 <
                        memo[target].num_coins) {
                        /** If found matching exceed amount, choose the
                         * solution that uses less coins. */
                        use_entry(remaining_target, coin_val);
                    }
                }
            }
        }
    }

    out.amt_paid  = memo[in.target_amt].exceeded + in.target_amt,
    out.coins_cnt = memo[in.target_amt].num_coins;

    return out;
}

void fmtout(const Output& out) {
    cout << out.amt_paid << " " << out.coins_cnt << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    fmtout(process(read_in()));
}
