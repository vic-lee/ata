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

// void exp_counting_sort(vector<unsigned int>& V, unsigned int exp) {
//     vector<unsigned int> counts(10, 0);
//     vector<unsigned int> output(V.size(), 0);
//     for (auto const& e : V)
//         counts[(e / exp) % 10]++;

//     // for (size_t i = 0; i < counts.size(); i++)
//     //     cout << i << ": " << counts[i] << "  ";
//     // cout << '\n';
//     for (size_t i = 1; i < counts.size(); i++)
//         counts[i] += counts[i - 1];
//     // for (size_t i = 0; i < counts.size(); i++)
//     //     cout << i << ": " << counts[i] << "  ";
//     // cout << '\n';

//     unsigned int key;
//     for (int i = V.size() - 1; i >= 0; i--) {
//         key = (V[i] / exp) % 10;
//         // cout << "assigning " << V[i] << " to position " << counts[key] - 1
//         //      << " (key: " << key << " " << (V[i] / exp) << " "
//         //      << ((V[i] / exp) % 10) << " " << counts[key] << ")" << '\n';
//         output[counts[key] - 1] = V[i];
//         counts[key]--;
//     }
//     copy(output.begin(), output.end(), V.begin());
// }

// void radix_sort(vector<unsigned int>& V) {
//     for (unsigned int exp = 1; MAX / exp > 0; exp *= 10) {
//         // cout << "doing exp " << exp << '\n';
//         exp_counting_sort(V, exp);
//     }
// }

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
    // sort(scores.begin(), scores.end());
    // radix_sort(scores);
    counting_sort(scores);
    fmtout(scores);
}
