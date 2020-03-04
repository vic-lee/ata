#include <iostream>
#include "ctype.h"

using namespace std;

int main() {
    string A, B;
    cin >> A >> B;
    for (unsigned int i = 0; i < A.size(); i++) {
        if (tolower(A[i]) < tolower(B[i])) {
            cout << -1;
            return 0;
        } else if (tolower(A[i]) > tolower(B[i])) {
            cout << 1;
            return 0;
        }
    }
    cout << 0;
}
