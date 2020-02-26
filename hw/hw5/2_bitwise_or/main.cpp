#include <bitset>
#include <iostream>

using namespace std;
using ULL = unsigned long long;

int main() {
    ULL raw_N, raw_L, raw_R;
    cin >> raw_N >> raw_L >> raw_R;
    if (raw_L == raw_R) {
        cout << raw_L << endl;
        return 0;
    }

    auto N = bitset<32>(raw_N), R = bitset<32>(raw_R), L = bitset<32>(raw_L);
    // suppose answer is the upper limit. we then turn off unnecessary bits.
    auto A = bitset<32>(raw_R);

    bool l_msb_found = raw_L == 0, r_msb_found = raw_R == 0;

    for (int i = 31; i >= 0; i--) {
        // test L & R's MSBs
        if (!l_msb_found && L.test(i))
            l_msb_found = true;
        if (!r_msb_found && R.test(i))
            r_msb_found = true;

        // only start modifying if we have reached R's most significant bit.
        if (r_msb_found) {
            if (L.test(i) && R.test(i)) { /* both bits are set */
                if (N.test(i)) {
                    A.reset(i);
                    if (A.to_ullong() < raw_L)
                        A.set(i);
                } else {
                    A.set(i);
                }
            } else if (L.test(i)) { /* only bit in L is set */
                A.set(i, !N.test(i));
                if (A.to_ullong() > raw_R)
                    A.set(i, N.test(i));
            } else if (R.test(i)) { /* only bit in R is set */
                A.set(i, !N.test(i));
            } else { /* neither bits are set */
                if (r_msb_found) {
                    A.set(i, !N.test(i));
                    if (A.to_ullong() > raw_R)
                        A.set(i, N.test(i));
                }
            }
        }
    }

    cout << A.to_ullong() << endl;
}
