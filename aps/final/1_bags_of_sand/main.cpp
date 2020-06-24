#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
using MinQueue = priority_queue<T, vector<T>, greater<T>>;

#define FOR_N(n) for (int i = 0; i < n; i++)

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

MinQueue<UIN> read_in() {
    UIN num_bags;
    cin >> num_bags;
    MinQueue<UIN> nums;

    UIN bag;
    FOR_N(num_bags) {
        cin >> bag;
        nums.push(bag);
    }

    return nums;
}

ULL min_bagging_cost(MinQueue<UIN>& bags) {
    ULL total_cost = 0;

    do {
        auto bag1 = bags.top();
        bags.pop();
        auto bag2 = bags.top();
        bags.pop();
        auto new_bag_cost = bag1 + bag2;
        total_cost += new_bag_cost;
        bags.push(new_bag_cost);
    } while (bags.size() >= 2);

    return total_cost;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    cout << min_bagging_cost(in) << endl;
}
