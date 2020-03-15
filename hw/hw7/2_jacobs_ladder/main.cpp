#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using UIN = unsigned int;

vector<UIN> read_in() {
    UIN len, next;
    cin >> len;
    vector<UIN> steps(len, 0);
    for (size_t i = 0; i < len; i++) {
        cin >> next;
        steps[i] = next;
    }
    return steps;
}

UIN min_energy(vector<UIN>& steps) {
    if (steps.size() == 0)
        return 0;
    else if (steps.size() == 1)
        return steps[0];

    adjacent_difference(steps.begin(), steps.end(), steps.begin());

    UIN req = steps.back();
    for (auto it = steps.rbegin() + 1; it != steps.rend(); it++)
        req = *it == req ? req + 1 : max(req, *it);

    return req;
}

int main() {
    auto steps = read_in();
    cout << min_energy(steps) << endl;
}
