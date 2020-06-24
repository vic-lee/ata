#include <float.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Input {
    double rod_len;
    double temperature;
    double expand_coef;
};

Input read_in() {
    Input in;
    cin >> in.rod_len >> in.temperature >> in.expand_coef;
    return in;
}

constexpr double expanded_len(double L, double T, double C) {
    return L * (1 + T * C);
}

inline double calc(double theta) { return sin(theta) / theta; }

void process(const Input& in) {
    const double eps = exp(-32);

    double arc_len = expanded_len(in.rod_len, in.temperature, in.expand_coef);
    double target  = in.rod_len / arc_len;
    double theta_lower = 0, theta_upper = M_PI, theta_mid;

    if (arc_len == in.rod_len || in.rod_len == 0) {
        cout << "0.000" << endl;
        return;
    }

    do {
        theta_mid  = (theta_lower + theta_upper) / 2;
        double res = calc(theta_mid) - target;
        if (res > eps) {
            theta_lower = theta_mid;
        } else if (res < -eps) {
            theta_upper = theta_mid;
        } else {
            break;
        }
        // cout << theta_lower << ", " << theta_upper << ", " << res << endl;
    } while (theta_upper >= theta_lower);

    double R   = 0.5 * arc_len / theta_mid;
    double R_d = 0.5 * in.rod_len / tan(theta_mid);
    double d   = R - R_d;

    cout << fixed << setprecision(3) << d << endl;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
