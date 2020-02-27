#include <algorithm>
#include <bitset>
#include <cctype>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

#define MAX_LINE_LEN 200

using namespace std;

template <typename T>
void print_vect(T vect) {
    for (auto& v : vect)
        cout << v << endl;
}

vector<string> read_in() {
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    return lines;
}

void fmtout(map<string, bool>& dict) {
    for (auto& w : dict) {
        cout << w.first << endl;
    }
}

inline string tolowerstr(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

map<string, bool> parse(vector<string>& lines) {
    map<string, bool> words;

    for (auto& line : lines) {
        regex delim("[^a-zA-Z+]");
        auto it = sregex_token_iterator(line.begin(), line.end(), delim, -1),
             end = sregex_token_iterator();
        while (it != end) {
            auto word = it->str();
            if (word.size() > 0) {
                word = tolowerstr(word);
                words[word] = true;
            }
            it++;
        }
    }

    return words;
}

int main() {
    auto lines = read_in();
    auto dict = parse(lines);
    fmtout(dict);
}
