#include <algorithm>
#include <cmath>
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

    const ULL blocks_sum = accumulate(blocks.begin(), blocks.end(), 0);

    std::set<size_t> tower_elems;
    int              target   = blocks_sum / 2;
    int              tower_sz = blocks.size() / 2;
    int tower_sum = accumulate(blocks.begin(), blocks.begin() + tower_sz, 0);

    for (size_t i = 0; i < tower_sz; i++) {
        tower_elems.insert(i);
    }

    for (size_t i = tower_sz; i < blocks.size(); i++) {
        int curr_delta        = abs(tower_sum - target);
        int best_delta        = curr_delta;
        int block_candidate   = blocks[i];
        int removal_candidate = -1;

        for (auto const elem : tower_elems) {
            int this_delta =
                abs(tower_sum - blocks[elem] + block_candidate - target);
            if (this_delta < best_delta) {
                removal_candidate = elem;
                best_delta        = this_delta;
            }
        }

        if (removal_candidate != -1) {
            tower_elems.erase(removal_candidate);
            tower_elems.insert(i);
            tower_sum = 0;
            for (auto const elem : tower_elems) {
                tower_sum += blocks[elem];
            }
        }
    }

    int block1 = tower_sum, block2 = blocks_sum - tower_sum;
    if (block1 > block2) swap(block1, block2);
    std::cout << block1 << " " << block2 << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    construct_blocks(in);
}
