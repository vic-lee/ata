#include <bits/stdc++.h>
using namespace std;

#define N 1000000
int rep[N];
int rnk[N];

void init(int k) {
    for (int i = 0; i < k; ++i) {
        rnk[i] = 0;
        rep[i] = i;
    }
}

int find(int k) {
    if (rep[k] == k) return k;
    return rep[k] = find(rep[k]);
}

void unionset(int a, int b) {
    a = find(a);
    b = find(b);
    if (rnk[a] > rnk[b]) swap(a, b);
    if (rnk[a] == rnk[b]) rnk[a]++;
    rep[b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    init(n);
    cin.ignore();
    while (q--) {
        int  a, b;
        char op;
        cin >> op >> a >> b;
        if (op == '=') {
            unionset(a, b);
        } else {
            if (find(a) == find(b))
                cout << "yes\n";
            else
                cout << "no\n";
        }
    }
    return 0;
}