#include <iostream>
#include <vector>

using namespace std;

bool has_conflict(vector<vector<int>> reqs) {
    vector<bool> bst;
    for (auto& r : reqs) {
        if (r[1] > bst.size())
            bst.resize(r[1]);

        if (r.size() == 2) {
            for (int i = r[0]; i < r[1]; i++) {
                if (bst[i])
                    return true;
                bst[i] = true;
            }
        } else {
            for (int c = 0; c < r[2]; c++) {
                for (int i = r[0]; i < r[1]; i++) {
                    if (bst[i])
                        return true;
                    bst[i] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    int a, b, c;
    unsigned int onetime_cnt, repeat_cnt;
    cin >> onetime_cnt >> repeat_cnt;
    vector<vector<int>> reqs;
    vector<string> outputs;

    while (cin >> a >> b) {
        if (a == 0 && b == 0) {
            bool conflicts = has_conflict(reqs);
            if (conflicts)
                outputs.push_back("CONFLICT");
            else
                outputs.push_back("NO CONFLICT");
            break;
        }
        if (onetime_cnt == 0 && repeat_cnt == 0) {
            bool conflicts = has_conflict(reqs);
            if (conflicts)
                outputs.push_back("CONFLICT");
            else
                outputs.push_back("NO CONFLICT");
            reqs.clear();
            onetime_cnt = a, repeat_cnt = b;
            continue;
        }
        if (onetime_cnt != 0) {
            auto next_vect = {a, b};
            reqs.push_back(next_vect);
            onetime_cnt--;
        } else  // this is a repeated task
        {
            cin >> c;
            auto next_vext = {a, b, c};
            reqs.push_back(next_vext);
            c = 0;
            repeat_cnt--;
        }
    }

    for (auto& o : outputs)
        cout << o << endl;
}