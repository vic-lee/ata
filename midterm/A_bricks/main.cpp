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

    unsigned int N, x, sum = 0, min_moves = 0;
    cin >> N;
    vector<UIN> nums(N, 0);
    for (size_t i = 0; i < N; i++) {
        cin >> x;
        nums[i] = x;
        sum += x;
    }
    UIN avg = sum / N;  // always divisible
    for (size_t i = 0; i < N; i++) {
        if (nums[i] > avg) {
            min_moves += nums[i] - avg;
        }
    }

    cout << "The minimum number of moves is " << min_moves << "." << endl;
}
