#include <iostream>
#include <sstream>
#include <vector>

#define FOR_N(n) for (int i = 0; i < n; i++)

#define MAX_ISLAND_ID 30000

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

struct Input {
    vector<int> gem_count = vector<int>(MAX_ISLAND_ID + 1, 0);
    UIN         first_jump_len;
};

Input read_in() {
    Input in;
    UIN   gem_input_count;
    std::cin >> gem_input_count >> in.first_jump_len;

    UIN loc;
    FOR_N(gem_input_count) {
        std::cin >> loc;
        in.gem_count[loc]++;
    }

    return in;
}

int collect_gems(Input& in) {
    // memo[i] stores the number of gems collectable in locations i ... 30000.
    std::vector<int> memo(30001, INT_MAX);

    // collect(remaining_dist, prior_jump)
    // collect(-*, *) = 0   // invalid case, ignore
    // collect(0, *) = 0
    // collect(n, j) = max(
    //      collect(n-(j-1), j-1)
    //      collect(n-j,     j)
    //      collect(n-(j+1), j+1)
    // )
    //
    std::function<int(int, int)> collect = [&](int curr_island,
                                               int prior_jump) {
        if (prior_jump <= 0) return 0;
        if (curr_island >= 30000) return 0;
        if (memo[curr_island] != INT_MAX) return memo[curr_island];

        int ans =
            max(collect(curr_island + (prior_jump + 1), prior_jump + 1),
                max(collect(curr_island + prior_jump, prior_jump),
                    collect(curr_island + (prior_jump - 1), prior_jump - 1)));

        ans += in.gem_count[curr_island];
        memo[curr_island] = ans;
        return ans;
    };

    return collect(0, in.first_jump_len);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    std::cout << collect_gems(in) << std::endl;
}
