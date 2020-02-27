#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

struct Instruction {
    char inst;
    int a;
    int b;
};

int main() {
    int N, Q;
    ostringstream oss;
    vector<Instruction> insts;
    cin >> N >> Q;

    for (int i = 0; i < Q; ++i) {
        Instruction ix;
        cin >> ix.inst >> ix.a >> ix.b;
        insts.push_back(ix);
    }

    map<int, int> base_set;
    map<int, set<int>> sets;
    for (int i = 1; i <= N; ++i) {
        base_set[i] = i;
        sets[i] = set<int>();
        sets[i].insert(i);
    }

    for (auto& ix : insts) {
        switch (ix.inst) {
            case '?':
                if (base_set[ix.a] == base_set[ix.b]) {
                    oss << "yes\n";
                } else {
                    oss << "no\n";
                }
                break;
            case '=':
            default:
                if (base_set[ix.a] == base_set[ix.b]) {
                    break;
                } else {
                    auto set_A = sets[ix.a];
                    auto set_B = sets[ix.b];
                    auto to_remove =
                        set_A.size() < set_B.size() ? &set_A : &set_B;
                    int target = set_A.size() < set_B.size() ? base_set[ix.b]
                                                             : base_set[ix.a];
                    for (auto it = to_remove->begin(); it != to_remove->end();
                         it++) {
                        set_A.insert(*it);
                        base_set[*it] = target;
                    }
                    sets[ix.b] = set_A;
                }
                break;
        }
    }

    cout << oss.str() << endl;
}
