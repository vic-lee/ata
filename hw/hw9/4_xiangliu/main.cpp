#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

#define IMPOSSIBLE_OUTPUT "Xia is doomed!"
#define IMPOSSIBLE_OUTPUT_CODE -1

using namespace std;
using UIN = unsigned int;
using MinQueue = priority_queue<UIN, vector<UIN>, greater<UIN>>;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Input {
    MinQueue heads;
    MinQueue archers;
    bool xia_doomed = false;
};

Input read_in() {
    Input in;

    UIN head_cnt, archer_cnt, x;
    cin >> head_cnt >> archer_cnt;

    if (head_cnt > archer_cnt) {
        in.xia_doomed = true;
        return in;
    }

    for (size_t i = 0; i < head_cnt; i++) {
        cin >> x;
        in.heads.push(x);
    }

    for (size_t i = 0; i < archer_cnt; i++) {
        cin >> x;
        in.archers.push(x);
    }

    return in;
}

int match_archers(MinQueue& heads, MinQueue& archers) {
    int sum = 0;

    while (heads.size() > 0 && archers.size() > 0) {
        if (heads.top() <= archers.top()) {
            sum += archers.top();
            archers.pop();
            heads.pop();
        } else {
            archers.pop();
        }
    }

    if (heads.size() > 0) {
        return IMPOSSIBLE_OUTPUT_CODE;
    }

    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();

    if (in.xia_doomed) {
        cout << IMPOSSIBLE_OUTPUT << endl;
        return 0;
    }

    int ans = match_archers(in.heads, in.archers);
    if (ans < 0) {
        cout << IMPOSSIBLE_OUTPUT << endl;
    } else {
        cout << ans << endl;
    }
}
