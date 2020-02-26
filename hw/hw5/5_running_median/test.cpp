#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>

using namespace std;
using ULL = unsigned long long;

deque<unsigned int> read_in() {
    deque<unsigned int> nums;
    string line;
    unsigned int x;
    while (getline(cin, line)) {
        if (line.find_first_not_of(' ') == string::npos)
            break;
        istringstream iss(line);
        nums.push_back(*istream_iterator<unsigned int>{iss});
    }
    for (auto& n : nums)
        cout << n << ' ';
    cout << endl;
    return nums;
}

/**
 * Implements a brute-force running medians algorithm to test correctness.
 */
deque<ULL> find_running_medians(deque<unsigned int>& input) {
    deque<unsigned int> queue;
    deque<ULL> medians;
    ULL med;
    while (input.size()) {
        queue.push_back(input.front());
        input.pop_front();
        sort(queue.begin(), queue.end());

        if (queue.size() % 2 == 0) {
            med = ((ULL)queue[queue.size() / 2] +
                   (ULL)queue[queue.size() / 2 - 1]) /
                  2;
        } else {
            med = queue[queue.size() / 2];
        }
        medians.push_back(med);

        cout << med << '\t';
        for (auto& x : queue)
            cout << x << ' ';
        cout << endl;
    }
    return medians;
}

void fmtout(deque<ULL> medians) {
    for (auto& m : medians)
        cout << m << endl;
}

int main() {
    auto nums = read_in();
    auto meds = find_running_medians(nums);
    fmtout(meds);
}
