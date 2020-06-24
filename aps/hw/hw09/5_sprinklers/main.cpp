#include <bitset>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#define NUM_SPRINKLERS_LIMIT 10000

using namespace std;
using UIN = unsigned int;

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

struct Sprinkler {
    UIN id;
    UIN pos;
    UIN radius;
};

struct Input {
    UIN               L;
    UIN               W;
    vector<Sprinkler> sprinklers;
};

Input read_in() {
    Input in;
    UIN   num_sprinklers, pos, radius;
    cin >> num_sprinklers >> in.L >> in.W;
    in.sprinklers = vector<Sprinkler>(num_sprinklers);

    for (UIN i = 0; i < num_sprinklers; i++) {
        cin >> pos >> radius;
        in.sprinklers[i] = {i, pos, radius};
    }

    return in;
}

int process(Input& in) {
    auto   used  = bitset<NUM_SPRINKLERS_LIMIT>();
    int    count = 0;
    double cur   = 0;

    auto const has_intercept = [&in](const Sprinkler& sp) -> bool {
        return (double)sp.radius >= 0.5 * in.W;
    };

    auto const intercept_pos = [&in](const Sprinkler& sp, bool left) -> double {
        const double delta = sqrt(pow(sp.radius, 2) - pow(0.5 * in.W, 2));
        return left ? sp.pos - delta : sp.pos + delta;
    };

    unordered_map<UIN, double> left_intercepts, right_intercepts;

    for (auto const& sp : in.sprinklers) {
        if (has_intercept(sp)) {
            left_intercepts[sp.id]  = intercept_pos(sp, true);
            right_intercepts[sp.id] = intercept_pos(sp, false);
        }
    }

    auto const set_intercepts = [&left_intercepts, &right_intercepts,
                                 &intercept_pos](const Sprinkler& sp) {
        left_intercepts[sp.id]  = intercept_pos(sp, true);
        right_intercepts[sp.id] = intercept_pos(sp, false);
    };

    for_each_if(in.sprinklers.begin(), in.sprinklers.end(), set_intercepts,
                has_intercept);

    bool found_any = true;
    while (found_any && cur < in.L) {
        found_any = false;

        double max_right_intercept = 0;
        UIN    max_sprinker_id;

        auto const is_candidate =
            [&left_intercepts, &right_intercepts, &used, &cur, &found_any,
             &has_intercept](const Sprinkler& sp) -> bool {
            if (!has_intercept(sp)) return false;

            bool found = !used.test(sp.id) && left_intercepts[sp.id] <= cur &&
                         right_intercepts[sp.id] >= cur;

            if (found) found_any = true;
            return found;
        };

        auto const take_max_right_intercept =
            [&max_right_intercept, &max_sprinker_id,
             &right_intercepts](const Sprinkler& sp) {
                if (right_intercepts[sp.id] > max_right_intercept) {
                    max_sprinker_id     = sp.id;
                    max_right_intercept = right_intercepts[sp.id];
                }
            };

        for_each_if(in.sprinklers.begin(), in.sprinklers.end(),
                    take_max_right_intercept, is_candidate);

        if (found_any) {
            used.set(max_sprinker_id);
            cur = max_right_intercept;
            count++;
        } else {
            count = -1;
        }
    }

    return count;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(in) << endl;
}
