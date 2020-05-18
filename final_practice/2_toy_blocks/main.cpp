#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#define FOR_N(n) for (int i = 0; i < n; i++)

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

std::vector<int> read_in() {
    UIN block_count;
    std::cin >> block_count;
    std::vector<int> blocks(block_count, 0);

    FOR_N(block_count) cin >> blocks[i];

    return blocks;
}

void construct_blocks(const vector<int>& blocks) {
    if (blocks.size() == 1) {
        std::cout << "0 " << blocks[0] << std::endl;
        return;
    }

    if (blocks.size() == 2) {
        int block1 = blocks[0], block2 = blocks[1];
        if (block1 > block2) swap(block1, block2);
        std::cout << block1 << " " << block2 << std::endl;
        return;
    }

    const int blocks_sum = accumulate(blocks.begin(), blocks.end(), 0);

    const int tower_sz_lowerlim = blocks.size() / 2;
    const int tower_sz_upperlim = blocks.size() - tower_sz_lowerlim;

    // memoizes the minimum absolute difference between the two tower's
    // sums, for each tower sum and each tower size (height).
    vector<vector<int>> memo(blocks_sum + 1,
                             vector<int>(blocks.size() + 1, -1));

    std::function<int(size_t, int, int)> minimize_diff =
        [&](size_t curr, int curr_tower_sum, int tower_sz) {
            // cout << curr << " " << curr_tower_sum << " " << tower_sz << endl;

            if (curr > blocks.size() - 1) return INT_MAX;
            if (curr == blocks.size() - 1) {
                if (tower_sz >= tower_sz_lowerlim &&
                    tower_sz <= tower_sz_upperlim) {
                    return abs(blocks_sum - curr_tower_sum - curr_tower_sum);
                }
                return INT_MAX;
            }
            if (tower_sz > tower_sz_upperlim) return INT_MAX;

            if (memo[curr_tower_sum][tower_sz] != -1) {
                return memo[curr_tower_sum][tower_sz];
            }

            int res = min(minimize_diff(curr + 1, curr_tower_sum + blocks[curr],
                                        tower_sz + 1),
                          minimize_diff(curr + 1, curr_tower_sum, tower_sz));

            memo[curr_tower_sum][tower_sz]                              = res;
            memo[blocks_sum - curr_tower_sum][blocks.size() - tower_sz] = res;

            return res;
        };

    int min_diff = minimize_diff(0, 0, 0);
    // cout << min_diff << endl;
    int block1 = (blocks_sum - min_diff) / 2;
    int block2 = blocks_sum - block1;

    if (block1 > block2) swap(block1, block2);
    std::cout << block1 << " " << block2 << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    construct_blocks(in);
}
