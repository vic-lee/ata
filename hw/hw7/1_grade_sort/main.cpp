#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

#define MAX 100

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

void counting_sort(vector<unsigned int>& V) {
    vector<unsigned int> counts(101, 0);
    for (auto const& e : V)
        counts[e]++;
    size_t i = 0;
    for (size_t k = 0; k < counts.size(); k++) {
        if (counts[k] > 0) {
            fill(V.begin() + i, V.begin() + i + counts[k] + 1, k);
            i += counts[k];
        }
    }
}

void fmtout(const vector<unsigned int>& V) {
    copy(begin(V), prev(end(V)), ostream_iterator<int>(cout, " "));
    cout << *prev(end(V)) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto scores = read_in();
    counting_sort(scores);
    fmtout(scores);
}
