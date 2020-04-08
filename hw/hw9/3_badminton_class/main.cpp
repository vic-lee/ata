#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    UIN male_cnt, female_cnt;
    cin >> male_cnt >> female_cnt;
    vector<UIN> males(male_cnt, 0);
    for (size_t i = 0; i < male_cnt; i++) cin >> males[i];

    vector<UIN> females(female_cnt, 0);
    for (size_t i = 0; i < female_cnt; i++) cin >> females[i];

    if (male_cnt <= female_cnt) {
        cout << 0 << endl;
        return 0;
    } else {
        cout << (male_cnt - female_cnt) << ' '
             << *min_element(males.begin(), males.end()) << endl;
    }
}
