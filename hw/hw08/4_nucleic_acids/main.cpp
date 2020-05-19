#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;
using CountIntersionContainer = vector<char>;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const &item : items) {
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

struct Entry {
    ULL inversion_cnt;
    vector<char> src;

    bool operator<(const Entry &str) const {
        return inversion_cnt < str.inversion_cnt;
    }
};

vector<Entry> read_in() {
    UIN str_len, str_cnt;
    cin >> str_len >> str_cnt;
    vector<Entry> strs(str_cnt, {0, vector<char>(str_len, ' ')});

    for (size_t i = 0; i < str_cnt; i++) {
        for (size_t j = 0; j < str_len; j++) {
            cin >> strs[i].src[j];
        };
    }

    return strs;
}

ULL count_inversions(const CountIntersionContainer &items) {
    int inv_cnt = 0;

    for (int i = 0; i < items.size() - 1; i++)
        for (int j = i + 1; j < items.size(); j++)
            if (items[i] > items[j]) inv_cnt++;

    return inv_cnt;
}

void calc(vector<Entry> &strs) {
    for (auto &str : strs) str.inversion_cnt = count_inversions(str.src);
    stable_sort(strs.begin(), strs.end());
}

void fmtout(vector<Entry> &strs) {
    ostringstream oss;
    for (auto const &str : strs) {
        for (auto const &c : str.src) {
            oss << c;
        }
        oss << '\n';
    }
    cout << oss.str();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto strs = read_in();
    calc(strs);
    fmtout(strs);
}
