#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<unsigned int> read_in() {
    unsigned int N;
    string line;

    getline(cin, line);
    N = (unsigned int)atoi(&line[0]);

    // get line of space-separated, N numbers.
    getline(cin, line);

    istringstream iss(line);
    vector<unsigned int> scores(N, 0);

    string tmp;
    for (size_t i = 0; i < N; i++) {
        iss >> tmp;
        scores[i] = (atoi(tmp.c_str()));
    }

    return scores;
}

void fmtout(const vector<unsigned int>& V) {
    copy(begin(V), prev(end(V)), ostream_iterator<int>(cout, " "));
    cout << *prev(end(V)) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto scores = read_in();
    sort(scores.begin(), scores.end());
    fmtout(scores);
}
