#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
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

void find_root(const int A, const int B, const int C, const int D, const int E,
               const int F, double& ans, bool& found) {
    double left = 0, right = 1, mid = (left + right) / 2;
    const double EPSILON = 0.0001;
    found = true;

    /** calculates the value of the function */
    auto calc = [A, B, C, D, E, F](double x) {
        return A * exp(-x) + B * sin(x) + C * cos(x) + D * tan(x) +
               E * pow(x, 2) + F;
    };

    /** checks for root accuracy */
    auto root_found = [EPSILON](double a) { return abs(a) < EPSILON; };

    double left_res = calc(left), right_res = calc(right), mid_res = 1;

    if (root_found(left_res)) {
        ans = left;
        return;
    } else if (root_found(right_res)) {
        ans = right;
        return;
    }

    // no solution if left and right solution are of the same sign
    if (signbit(left_res) == signbit(right_res)) {
        found = false;
        return;
    }

    mid_res = calc(mid);

    do {
        // either left or right cursor will get adjusted
        right = signbit(left_res) != signbit(mid_res) ? mid : right;
        left = signbit(right_res) != signbit(mid_res) ? mid : left;
        mid = (left + right) / 2;
        mid_res = calc(mid);
    } while (!root_found(mid_res));

    ans = mid;
    return;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d, e, f;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

    double ans;
    bool root_found;

    find_root(a, b, c, d, e, f, ans, root_found);

    if (root_found)
        cout << fixed << setprecision(4) << ans << endl;
    else
        cout << "No solution" << endl;
}
