#include <cmath>
#include <iostream>
#include <numeric>
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

struct Blocks {
    int block1;
    int block2;
};

Blocks construct_blocks(const vector<int>& blocks) {
    int global_block_1 = 0, global_block_2 = 0;
    ULL blocks_sum = accumulate(blocks.begin(), blocks.end(), 0);

    if (blocks.size() % 2 == 0) {
        size_t block_sz = blocks.size() / 2;
        if (block_sz % 2 == 0) {
            global_block_1 =
                accumulate(blocks.begin() + block_sz / 2,
                           blocks.begin() + block_sz / 2 + block_sz, 0);
            global_block_2 = blocks_sum - global_block_1;
        } else {
            ULL    local_block_1 = 0, local_block_2 = 0;
            size_t start_idx = (block_sz - 1) / 2;

            local_block_1 =
                accumulate(blocks.begin() + start_idx,
                           blocks.begin() + start_idx + block_sz, 0);
            local_block_2  = blocks_sum - local_block_1;
            global_block_1 = local_block_1;
            global_block_2 = local_block_2;

            // phase 2
            local_block_1 = local_block_1 + blocks[start_idx + block_sz] -
                            blocks[start_idx];
            local_block_2 = blocks_sum - local_block_1;

            if (abs((int)(local_block_1 - local_block_2)) <
                abs((int)(global_block_1 - global_block_2))) {
                global_block_1 = local_block_1;
                global_block_2 = local_block_2;
            }
        }
    } else {
        size_t start_idx = (blocks.size() - 1) / 4;
        size_t end_idx   = start_idx + (blocks.size() - 1) / 2;

        int local_block_1 = 0, local_block_2 = 0;
        local_block_1 =
            accumulate(blocks.begin() + start_idx, blocks.begin() + end_idx, 0);
        local_block_2 = blocks_sum - local_block_1;

        global_block_1 = local_block_1;
        global_block_2 = local_block_2;

        // phase 2
        local_block_1 = local_block_1 + blocks[end_idx] - blocks[start_idx];
        local_block_2 = blocks_sum - local_block_1;

        if (abs(local_block_1 - local_block_2) <
            abs(global_block_1 - global_block_2)) {
            global_block_1 = local_block_1;
            global_block_2 = local_block_2;
        }

        // phase 3
        local_block_1 += blocks[start_idx];
        local_block_2 = blocks_sum - local_block_1;

        if (abs(local_block_1 - local_block_2) <
            abs(global_block_1 - global_block_2)) {
            global_block_1 = local_block_1;
            global_block_2 = local_block_2;
        }
    }

    if (global_block_1 > global_block_2) swap(global_block_1, global_block_2);
    return {global_block_1, global_block_2};
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = construct_blocks(in);

    cout << out.block1 << " " << out.block2 << endl;
}
