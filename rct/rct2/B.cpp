#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> rowGen(int n) {
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(i);
    for (int i = n; i >= 0; i--) v.push_back(i);
    return v;
}

string rtrim(string s) {
    string whitespace = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(whitespace);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

string stringifyRow(vector<int> v, int n) {
    ostringstream ss;
    int diff = n - v.size() / 2;
    for (int i = 0; i < diff; i++) ss << "  ";
    for (auto &c : v) ss << c << " ";
    return rtrim(ss.str());
}

vector<string> stringifyOutput(vector<vector<int>> v, int n) {
    vector<string> out;
    for (auto &c : v) {
        out.push_back(stringifyRow(c, n));
    }
    return out;
}

/**
 * input format: 2 <= n <= 9
 */
vector<string> hankerchief(int n) {
    vector<vector<int>> v;
    for (int i = 0; i < n; i++) v.push_back(rowGen(i));
    for (int i = n; i >= 0; i--) v.push_back(rowGen(i));
    return stringifyOutput(v, n);
}

void output(const vector<string>& v) {
    ostringstream ss;
    for (auto &c: v) {
        ss << c << endl;
    }
    cout << ss.str() << endl;
}

int main() {
    int in;
    cin >> in;
    vector<string> out = hankerchief(in);
    output(out);
}
