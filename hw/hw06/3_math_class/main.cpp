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
        return true;
    return (s2 + s1) > (s1 + s2);
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
