#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

struct Test {
    UIN lower;
    UIN upper;
    float tax_rate;
};

vector<Test> read_in() {
    UIN num_cases;
    float A, B, T;
    cin >> num_cases;
    vector<Test> tests(num_cases);
    for (size_t i = 0; i < num_cases; i++) {
        cin >> A >> B >> T;
        tests[i] = {(UIN)round(A * 100), (UIN)round(B * 100), T};
    }
    return tests;
}

float rounding(float in) {
    float val = (int)(in * 100 + .5);
    return (float)val / 100;
}

UIN ATP(UIN x, float T) {
    return (UIN)round(x * (1 + T / 100));
}

UIN num_impossible_prices(Test in) {
    auto cur = in.lower;
    auto target_lower = ATP(in.lower, in.tax_rate);
    auto target_upper = ATP(in.upper, in.tax_rate);

    // cout << target_lower << ' ' << target_upper << endl;

    UIN impossible_cnt = target_upper - target_lower + 1;

    vector<bool> prices(impossible_cnt, true);
    for (size_t i = in.lower; i <= in.upper; i++) {
        auto p = ATP(i, in.tax_rate);
        // cout << p << endl;
        if (prices[p - target_lower])
            impossible_cnt--;
        prices[p - target_lower] = false;
    }

    return impossible_cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    auto tests = read_in();

    ostringstream oss;
    for (auto& test : tests) {
        oss << num_impossible_prices(test) << '\n';
    }
    cout << oss.str();
}
