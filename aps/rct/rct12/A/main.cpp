#include <cmath>
#include <iostream>
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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    UIN num_friends, num_bottles, bottle_volume, num_limes, num_lime_cuts,
        salt_grams, friend_drink_sz, friend_salt_grams;

    cin >> num_friends >> num_bottles >> bottle_volume >> num_limes >>
        num_lime_cuts >> salt_grams >> friend_drink_sz >> friend_salt_grams;

    UIN num_drinks = num_bottles * bottle_volume / friend_drink_sz;
    UIN num_salt   = salt_grams / friend_salt_grams;

    cout << (min(min(num_drinks, num_limes * num_lime_cuts), num_salt) /
             num_friends)
         << endl;
}
