#include <algorithm>
#include <climits>
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

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Output {
    string flavor_order;
    ULL    min_mvmt;

    bool operator<(const Output& other_out) const {
        return flavor_order < other_out.flavor_order;
    }
};

vector<vector<ULL>> read_in() {
    vector<vector<ULL>> candies(3, vector<ULL>(3, 0));

    for (size_t box_id = 0; box_id < 3; box_id++) {
        for (size_t candy_type = 0; candy_type < 3; candy_type++) {
            cin >> candies[box_id][candy_type];
        }
    }

    return candies;
}

void process(const vector<vector<ULL>>& candies) {
    ULL            min_sum = ULLONG_MAX;
    vector<Output> solutions;

    auto calc_sum = [&candies](size_t b, size_t g, size_t c) -> ULL {
        ULL sum = 0;

        for (size_t candy_type = 0; candy_type < 3; candy_type++) {
            for (size_t i = 0; i < 3; i++) {
                if ((candy_type == 0 && i != b) ||
                    (candy_type == 1 && i != g) ||
                    (candy_type == 2 && i != c)) {
                    sum += candies[candy_type][i];
                }
            }
        }

        return sum;
    };

    auto to_sequence = [](size_t x, size_t y, size_t z) {
        auto to_letter = [](size_t x) -> string {
            switch (x) {
                case 0:
                    return "B";
                case 1:
                    return "G";
                case 2:
                    return "C";
                default:
                    return " ";
            }
        };
        return to_letter(x) + to_letter(y) + to_letter(z);
    };

    for (size_t b_it = 0; b_it < 3; b_it++) {
        for (size_t g_it = 0; g_it < 3; g_it++) {
            for (size_t c_it = 0; c_it < 3; c_it++) {
                if (b_it == g_it || g_it == c_it || b_it == c_it) {
                    continue;
                }

                ULL    sum = calc_sum(b_it, g_it, c_it);
                Output out = {to_sequence(b_it, g_it, c_it), sum};
                if (sum < min_sum) {
                    min_sum = sum;
                    solutions.clear();
                    solutions.push_back(out);
                } else if (sum == min_sum) {
                    solutions.push_back(out);
                }
            }
        }
    }

    sort(solutions.begin(), solutions.end());

    cout << solutions[0].flavor_order << " " << solutions[0].min_mvmt << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
