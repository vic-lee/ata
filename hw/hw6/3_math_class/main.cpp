#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

vector<string> read_in() {
    unsigned int num_cnt;
    string line;
    cin >> num_cnt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, line);
    istringstream iss(line);
    vector<string> raw_nums(istream_iterator<string>{iss},
                            istream_iterator<string>());
    return raw_nums;
}

auto rank_num = [](string s1, string s2) {
    if (s1 == s2)
        return true;  // s1 s2's order doesn't matter if they're equal.
    // else they must differ at some digit
    for (size_t i = 0; i < min(s1.size(), s2.size()); i++) {
        if (s1[i] > s2[i]) {
            return false;  // encounter greater digit in s1, s1 ranks higher.
        } else if (s1[i] < s2[i]) {
            return true;  // encounter greater digit in s2, s2 ranks higher.
        }
    }
    // else one number must be exactly matching the other's first len(s)
    size_t shift = min(s1.size(), s2.size());
    string long_num = s1.size() > s2.size() ? s1 : s2;

    for (size_t i = 0; (i + shift) < long_num.size(); i++) {
        if (long_num[i + shift] > long_num[i]) {
            return s1.size() < s2.size();  // whoever longer ranks first
        } else if (long_num[i + shift] < long_num[i]) {
            return s1.size() > s2.size();  // whoever shorter ranks first
        }
    }

    return false;
};

ostringstream sort_nums(vector<string>& raw_nums) {
    ostringstream oss;
    priority_queue<string, vector<string>, decltype(rank_num)> out(rank_num);

    for (auto& n : raw_nums) {
        out.push(n);
    }

    while (out.size()) {
        oss << out.top();
        out.pop();
    }

    return oss;
}

int main() {
    auto raw_in = read_in();
    if (raw_in.size() == 1) {
        cout << raw_in[0] << endl;
        return 0;
    }
    auto oss = sort_nums(raw_in);
    cout << oss.str() << endl;
}
