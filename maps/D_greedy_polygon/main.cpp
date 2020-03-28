#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

#define PI 3.14159265358979323846264338327950288419

vector<vector<UIN>> read_in() {
    UIN num_testcases, N, L, D, G;
    cin >> num_testcases;
    vector<vector<UIN>> tests(num_testcases);
    for (size_t i = 0; i < num_testcases; i++) {
        cin >> N >> L >> D >> G;
        tests[i] = {N, L, D, G};
    }
    return tests;
}

inline double original_area(UIN N, UIN L) {
    double x = (2 * tan(((double)180 / N) * (PI / 180.0)));
    double apothem = ((double)L / x);
    return (N * L * apothem) / 2;
}

inline double greedy_area(UIN N, UIN L, UIN D, UIN G) {
    const auto orig_area = original_area(N, L);
    const auto circ_area = PI * pow(G * D, 2);
    const auto side_area = N * L * G * D;
    return orig_area + circ_area + side_area;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    auto nums = read_in();
    ostringstream oss;
    for (auto const& num : nums) {
        oss << setprecision(25) << greedy_area(num[0], num[1], num[2], num[3])
            << '\n';
    }
    cout << oss.str();
}
