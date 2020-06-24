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
    vector<int> box_specs = vector<int>(7, 0);
    for (size_t i = 1; i < 7; i++) cin >> box_specs[i];
    return box_specs;
}

constexpr UIN vol(UIN side_len) { return side_len * side_len * side_len; }

UIN process(vector<int> box_specs) {
    UIN pkg_count = 0;

    // 6x6 boxes occupy the entire package
    pkg_count += box_specs[6];
    box_specs[6] = 0;

    pkg_count += box_specs[5];
    // each pkg with a 5x5 box can hold a maximum of 11 more 1x1 boxes.
    box_specs[1] -= min(box_specs[1], box_specs[5] * 11);

    pkg_count += box_specs[4];
    // each pkg with a 4x4 box can hold a maximum of 5 more 2x2 boxes.
    UIN box_2_capacity = 5 * box_specs[4];
    if (box_2_capacity <= box_specs[2]) {
        box_specs[2] -= box_2_capacity;
    } else {
        // if there aren't enough 2x2 boxes to fill up the capacity,
        // use as many 1x1 boxes as possible to fill in.
        int remain_box_1_capacity = box_2_capacity - box_specs[2];
        box_specs[2]              = 0;
        box_specs[1] -= min(box_specs[1], remain_box_1_capacity);
    }

    // each pkg can fit up to 4 3x3 boxes.
    pkg_count += box_specs[3] / 4;
    int rem_3 = box_specs[3] % 4;
    if (rem_3) {
        // use 1 extra pkg to pack the remaining 3x3 boxes (1 <= rem <= 3)
        pkg_count += 1;
        switch (rem_3) {
            case 3:
                // can fit at most 1 2x2 box
                if (box_specs[2] >= 1) {
                    box_specs[2]--;
                    // still has space for at most 5 1x1 boxes
                    box_specs[1] -= min(box_specs[1], 5);
                } else {
                    // if there're no 2x2 boxes remaining,
                    // can pack at most 9 1x1 boxes.
                    box_specs[1] -= min(box_specs[1], 9);
                }
                break;
            case 2:
                // can fit at most 2 2x2 boxes; try to fit remaining space
                // with as many 1x1 boxes as possible.
                if (box_specs[2] >= 2) {
                    box_specs[2] -= 2;
                    box_specs[1] -= min(box_specs[1], 10);
                } else if (box_specs[2] == 1) {
                    box_specs[2]--;
                    box_specs[1] -= min(box_specs[1], 14);
                } else {
                    box_specs[1] -= min(box_specs[1], 18);
                }
                break;
            case 1: {
                int box2_use_count = min(box_specs[2], 5);
                box_specs[2] -= box2_use_count;
                int box1_limit = 6 * 6 - 3 * 3 - box2_use_count * 2 * 2;
                box_specs[1] -= min(box_specs[1], box1_limit);
                break;
            }
            default:
                break;
        }
    }

    // check if there are remaining 2x2s and 1x1s.
    pkg_count += box_specs[2] / 9;
    int rem_2 = box_specs[2] % 9;
    if (rem_2) {  // 1 <= rem < 9
        pkg_count++;
        box_specs[2] -= rem_2;
        box_specs[1] -= min(box_specs[1], 6 * 6 - rem_2 * 2 * 2);
    }

    pkg_count += box_specs[1] / 36;
    int rem_1 = box_specs[1] % 36;
    if (rem_1) {
        pkg_count++;
        box_specs[1] -= rem_1;
    }

    return pkg_count;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(move(in)) << endl;
}
