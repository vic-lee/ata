#include <bitset>
#include <iostream>
#include <map>
using namespace std;
using ULL = unsigned long long;

int main() {
    ULL N, L, R;
    cin >> N >> L >> R;

    ULL max_res = 0;
    ULL max_key = 0;

    map<ULL, ULL> ans_map;

    for (ULL i = L; i <= R; i++) {
        ans_map[i] = N | i;
        cout << i << '\t' << (N | i) << "\t\t" << bitset<10>(i) << '\t'
             << bitset<10>(N | i) << endl;
        if ((N | i) > max_res) {
            max_res = N | i;
            max_key = i;
        }
    }

    cout << '\n' << "Max ans: " << max_key << "\tMax res: " << max_res << endl;
}
