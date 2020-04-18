#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
using UIN      = unsigned int;
using ULL      = unsigned long long;
using VoidFunc = void (*)();

auto const PKG_SIDELEN    = 6;
auto const LOG_DEBUG_INFO = false;

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

auto DEBUG = [](auto db_func) {
    if (LOG_DEBUG_INFO) {
        db_func();
    }
};

vector<int> read_in() {
    vector<int> box_specs = vector<int>(6, 0);
    for (size_t i = 0; i < 6; i++) cin >> box_specs[i];
    return box_specs;
}

constexpr UIN vol(UIN side_len) { return side_len * side_len * side_len; }

constexpr UIN idx(int side_len) { return side_len - 1; }

UIN process(vector<int> box_specs) {
    int pkg_remaining_vol    = vol(PKG_SIDELEN);
    int used_pkg_count       = 0;
    int max_sidelen_to_use   = 6;
    int usable_sidelen_limit = 6;
    int box_count = accumulate(box_specs.begin(), box_specs.end(), 0);

    auto find_next_max_sidelen = [&usable_sidelen_limit, &box_specs]() -> int {
        int cur = usable_sidelen_limit - 1;
        while (cur >= 0 && box_specs[cur] == 0) cur--;
        return cur + 1;
    };

    auto has_box = [&box_specs](UIN next_sidelen) -> bool {
        return box_specs[idx(next_sidelen)] > 0;
    };

    auto pkg_has_space = [&pkg_remaining_vol](UIN next_sidelen) -> bool {
        return pkg_remaining_vol >= vol(next_sidelen);
    };

    auto sidelen_fits_in_pkg =
        [&usable_sidelen_limit](UIN next_sidelen) -> bool {
        return next_sidelen <= usable_sidelen_limit;
    };

    auto can_use_box = [has_box, sidelen_fits_in_pkg, &usable_sidelen_limit,
                        pkg_has_space](UIN next_sidelen) -> bool {
        DEBUG([=]() {
            if (!has_box(next_sidelen)) {
                cout << "rejecting use box call; no box of " << next_sidelen
                     << " remains." << endl;
            }
            if (!sidelen_fits_in_pkg(next_sidelen)) {
                cout << "rejecting use box call: requested len " << next_sidelen
                     << " exceeds max usable len " << usable_sidelen_limit
                     << endl;
            }
            if (!pkg_has_space(next_sidelen)) {
                cout << "rejecting use box call: pkg has no space." << endl;
            }
        });
        return has_box(next_sidelen) && sidelen_fits_in_pkg(next_sidelen) &&
               pkg_has_space(next_sidelen);
    };

    auto eager_use_box = [&pkg_remaining_vol, &usable_sidelen_limit, &box_count,
                          &box_specs](UIN sidelen_to_use) {
        int num_boxes_to_use =
            min(box_specs[idx(sidelen_to_use)],
                (int)(pkg_remaining_vol / vol(sidelen_to_use)));

        pkg_remaining_vol -= vol(sidelen_to_use) * num_boxes_to_use;
        box_specs[idx(sidelen_to_use)] -= num_boxes_to_use;
        box_count -= num_boxes_to_use;
        usable_sidelen_limit =
            min(PKG_SIDELEN - sidelen_to_use, sidelen_to_use);
        DEBUG([=]() {
            cout << "using box of len: " << sidelen_to_use
                 << "; remaining: " << box_specs[idx(sidelen_to_use)]
                 << "; usable sidelen lim: " << usable_sidelen_limit
                 << "; current pkg still has: " << pkg_remaining_vol << endl;
        });
    };

    auto should_make_new_pkg = [&max_sidelen_to_use,
                                &pkg_remaining_vol]() -> bool {
        return max_sidelen_to_use == 0 || pkg_remaining_vol == 0;
    };

    auto make_new_pkg = [&pkg_remaining_vol, &used_pkg_count,
                         &usable_sidelen_limit]() {
        used_pkg_count++;
        pkg_remaining_vol    = vol(PKG_SIDELEN);
        usable_sidelen_limit = PKG_SIDELEN;
        DEBUG([=]() {
            cout << "making new pkg; full pkg count: " << used_pkg_count
                 << endl;
        });
    };

    while (box_count > 0) {
        if (should_make_new_pkg()) {
            make_new_pkg();
            max_sidelen_to_use = find_next_max_sidelen();
        }

        if (can_use_box(max_sidelen_to_use)) eager_use_box(max_sidelen_to_use);

        max_sidelen_to_use = find_next_max_sidelen();
        DEBUG([=]() {
            cout << "getting next usable sidelen " << max_sidelen_to_use
                 << endl;
        });
    }

    return used_pkg_count + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(move(in)) << endl;
}
