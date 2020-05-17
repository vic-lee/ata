#include <algorithm>
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

    std::sort(blocks.begin(), blocks.end(), greater<int>());

    return blocks;
}

struct Tower {
    ULL sum;
    ULL height;

    Tower() {
        sum    = 0;
        height = 0;
    }

    void add(int x) {
        sum += x;
        height++;
    }
};

void construct_blocks(const vector<int>& rsorted_blocks) {
    if (rsorted_blocks.size() == 1) {
        std::cout << "0 " << rsorted_blocks[0] << std::endl;
        return;
    }

    if (rsorted_blocks.size() == 2) {
        std::cout << rsorted_blocks[1] << " " << rsorted_blocks[0] << std::endl;
    }

    const ULL blocks_sum =
        accumulate(rsorted_blocks.begin(), rsorted_blocks.end(), 0);

    Tower t1, t2;
    t1.add(rsorted_blocks[0]);
    t2.add(rsorted_blocks[1]);

    for (size_t i = 2; i < rsorted_blocks.size(); i++) {
        auto curr_block = rsorted_blocks[i];
        if (t1.height == t2.height) {
            if (t1.sum < t2.sum) {
                t1.add(curr_block);
            } else {
                t2.add(curr_block);
            }
        } else if (t1.height < t2.height) {
            t1.add(curr_block);
        } else {  // t1.height > t2.height
            t2.add(curr_block);
        }
    }

    if (t1.sum > t2.sum) {
        Tower tmp = t1;
        t1        = t2;
        t2        = tmp;
    }

    std::cout << t1.sum << " " << t2.sum << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    construct_blocks(in);
}
