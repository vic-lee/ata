#include <algorithm>
#include <deque>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

vector<vector<UIN>> read_in() {
    UIN updates_count, reviews_count;
    cin >> updates_count;
    vector<vector<UIN>> update_reviews(updates_count);

    for (size_t i = 0; i < updates_count; i++) {
        cin >> reviews_count;
        update_reviews[i] = vector<UIN>(reviews_count, 0);
        for (size_t j = 0; j < reviews_count; j++) {
            cin >> update_reviews[i][j];
        }
    }

    return update_reviews;
}

ostringstream process(vector<vector<UIN>>& update_reviews) {
    ostringstream oss;
    deque<UIN>    scores;

    for (auto const& reviews : update_reviews) {
        for (auto const& review_score : reviews) {
            scores.push_back(review_score);
        }
        sort(scores.begin(), scores.end());

        UIN max_score = scores.back();
        UIN min_score = scores.front();
        // cout << max_score << " " << min_score << endl;
        scores.pop_front();
        scores.pop_back();
        oss << (max_score - min_score) << '\n';
    }

    return oss;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << process(in).str();
}
