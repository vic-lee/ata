#include <iostream>
#include <map>
#include <set>
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

typedef function<bool(pair<UIN, UIN>, pair<UIN, UIN>)> Comparator;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    UIN num_count;
    cin >> num_count;
    vector<UIN> nums(num_count, 0);
    for (size_t i = 0; i < num_count; i++)
        cin >> nums[i];

    auto comp = [](std::pair<UIN, UIN> elem1, std::pair<UIN, UIN> elem2) {
        return elem1.second > elem2.second;
    };

    map<UIN, UIN> counts;
    for (auto const& num : nums)
        counts[num]++;

    set<pair<UIN, UIN>, Comparator> set(counts.begin(), counts.end(), comp);
    cout << set.begin()->second << " " << set.size() << endl;
}
