#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using UIN = unsigned int;

vector<UIN> read_in() {
    UIN num_scores, x;
    cin >> num_scores;
    vector<UIN> scores(num_scores, 0);
    for (size_t i = 0; i < num_scores; i++) {
        cin >> x;
        scores[i] = x;
    }
    return scores;
}

double calc_score(vector<UIN>& scores, int skip) {
    double score = 0.0;
    for (int i = 0; i < scores.size(); i++) {
        if (i < skip) {
            score += scores[i] * pow(0.8, i);
        } else if (i > skip) {
            score += scores[i] * pow(0.8, i - 1);
        } else {
            continue;
        }
    }
    return score / 5;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    auto scores = read_in();
    double sum_scores = 0.0;
    auto total_score = calc_score(scores, 52);
    for (size_t i = 0; i < scores.size(); i++) {
        sum_scores += calc_score(scores, i);
    }
    cout << setprecision(10) << total_score << '\n'
         << (sum_scores / scores.size()) << endl;
}
