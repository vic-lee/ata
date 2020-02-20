#include <iostream>
#include <vector>

using namespace std;

int main() {
    unsigned int num_cnt, x;
    cin >> num_cnt;
    vector<int> even, odd;
    for (int i = 1; i <= num_cnt; ++i) {
        cin >> x;
        if (x % 2 == 0) {
            even.push_back(i);
        } else {
            odd.push_back(i);
        }
    }
    cout << ((even.size() == 1) ? even.front() : odd.front()) << endl;
}
