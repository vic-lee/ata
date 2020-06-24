#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;
using UIN = unsigned int;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    UIN num_words;
    string word;
    getline(cin, line);
    num_words = (UIN)(stoi(line));
    unordered_set<string> words;
    for (size_t i = 0; i < num_words; i++) {
        getline(cin, word);
        replace(word.begin(), word.end(), '-', ' ');
        transform(word.begin(), word.end(), word.begin(),
                  [](unsigned char c) { return tolower(c); });
        words.insert(word);
    }

    cout << words.size() << endl;
}
