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

int optimize(int target, int tower_sz, const vector<int>& blocks) {
    std::set<size_t> tower_elems;

    int tower_sum = accumulate(blocks.begin(), blocks.begin() + tower_sz, 0);

    for (size_t i = 0; i < tower_sz; i++) {
        tower_elems.insert(i);
    }

    for (size_t i = tower_sz; i < blocks.size(); i++) {
        int curr_delta        = abs(tower_sum - target);
        int best_delta        = curr_delta;
        int block_candidate   = blocks[i];
        int removal_candidate = -1;

        if (curr_delta == 0) break;

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

    return tower_sum;
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

    int target   = blocks_sum / 2;
    int tower_sz = blocks.size() / 2;
    int block1, block2;

    if (blocks.size() % 2 == 0) {
        block1 = optimize(target, tower_sz, blocks);
        block2 = blocks_sum - block1;
    } else {
        int block1_c1 = optimize(target, tower_sz, blocks);
        int block2_c1 = blocks_sum - block1_c1;
        int block1_c2 = optimize(target, tower_sz + 1, blocks);
        int block2_c2 = blocks_sum - block1_c2;

        int c1_delta = abs(block1_c1 - block2_c1);
        int c2_delta = abs(block1_c2 - block2_c2);

        if (c1_delta <= c2_delta) {
            block1 = block1_c1;
            block2 = block2_c1;
        } else {
            block1 = block1_c2;
            block2 = block2_c2;
        }
    }

    if (block1 > block2) swap(block1, block2);
    std::cout << block1 << " " << block2 << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    construct_blocks(in);
}
