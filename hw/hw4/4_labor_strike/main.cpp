#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

#define STRIKE_FREQ_UNDEF 7
#define MAX_DURATION 3650

struct Input {
    unsigned int duration;
    vector<unsigned int> strike_freqs;
};

Input read_in() {
    Input in;
    unsigned int union_cnt, x;
    cin >> in.duration >> union_cnt;
    in.strike_freqs = vector<unsigned int>(union_cnt, STRIKE_FREQ_UNDEF);

    for (int i = 0; i < union_cnt; i++) {
        cin >> x;
        in.strike_freqs[i] = x;
    }

    return in;
}

inline bool is_day(unsigned int test, unsigned int day) {
    return test % 7 == day;
}

inline bool is_fri(unsigned int day) {
    return is_day(day, 5);
}

inline bool is_sat(unsigned int day) {
    return is_day(day, 6);
}

unsigned int count_strikes(vector<unsigned int> strike_freqs,
                           unsigned int duration) {
    auto bs = bitset<MAX_DURATION>();
    for (auto const& freq : strike_freqs) {
        unsigned int cur = freq - 1;
        while (cur < duration) {
            if (!is_fri(cur) && !is_sat(cur)) {
                bs.set(cur);
            }
            cur += freq;
        }
    }
    return bs.count();
}

int main() {
    auto in = read_in();
    cout << count_strikes(in.strike_freqs, in.duration) << endl;
}
