#include <iostream>
#include <sstream>
#include <deque>
#include <map>

using namespace std;

using NumContainer = deque<char>;
using base = int;

map<char, int> HexToDecMap = {
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},
};

map<char, int> DecToHexMap = {
    {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
};

int mapToDec(char s) {
    int r;
    if (isdigit(s)) {
        r = (int) s - 48;
    } else {
        r = HexToDecMap.at(s);
    }
    return r;
}

char mapToHex(int n) {
    if (n < 10) {
        ostringstream oss;
        oss << n;
        return oss.str()[0];
    } else {
        return DecToHexMap.at(n);
    }
}

/** Given a base-10 number, outputs a number in a new base. */
NumContainer from10(long n, base b) {
    NumContainer v;
    if (n == 0) {
        v.push_back('0');
        return v;
    }
    while (n > 0) {
        v.push_front(mapToHex(n % b));
        n = n / b;
    }
    return v;
}

/** Outputs the base-10 value of a number, given its base. */
long to10(const NumContainer& n, base b) {
    long ans = 0;
    for (const auto& d : n) {
        const int toAdd = mapToDec(d);
        if (toAdd >= b) {
            throw logic_error("invalid num");
        }
        ans = ans * b + toAdd;
    }
    return ans;
}

NumContainer split(string& s) {
    return NumContainer(s.begin(), s.end());
}

string join(const NumContainer& v) {
    string s(v.begin(), v.end());
    return s;
}

int main() {
    base fromBase, toBase;
    string numInput;
    cin >> fromBase >> toBase >> numInput;
    const NumContainer number = split(numInput);
    try {
        const string out = join(from10(to10(number, fromBase), toBase));
        printf("%s base %d = %s base %d", numInput.c_str(), fromBase, out.c_str(), toBase);
    } catch (exception& e) {
        printf("%s is an illegal base %d number", numInput.c_str(), fromBase);
        return 0;
    }
}