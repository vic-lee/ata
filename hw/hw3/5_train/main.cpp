#include <deque>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct Input {
    int train_size;
    vector<deque<int>> train_specs;
};

deque<int> parse_ints(string s, int size) {
    stringstream ss(s);
    deque<int> sol(size, 0);
    int i = 0;
    while (true) {
        int n;
        ss >> n;
        if (!ss) {
            break;
        }
        sol[i] = n;
        i++;
    }
    return sol;
}

Input read_input() {
    Input in;
    string nextLine;

    getline(cin, nextLine);
    stringstream ss(nextLine);
    ss >> in.train_size;

    while (getline(cin, nextLine)) {
        auto next = parse_ints(nextLine, in.train_size);
        if (next[0] == 0) {
            break;
        } else {
            in.train_specs.push_back(next);
        }
    }
    return in;
}

string is_train_valid(deque<int> spec, int train_len) {
    deque<int> train(train_len, 0);
    stack<int> stk;

    for (int i = 0; i < train_len; i++) {
        train[i] = i + 1;
    }

    while (spec.size() > 0 && train.size() > 0) {
        if (spec.front() > train[0]) {
            stk.push(train[0]);
            train.pop_front();
        } else if (spec.front() < train[0]) {
            if (stk.top() != spec.front()) {
                return "No";
            } else {
                stk.pop();
                spec.pop_front();
            }
        } else {
            train.pop_front();
            spec.pop_front();
        }
    }

    if (spec.size() > 0) {
        if (stk.size() == 0) {
            return "No";
        } else {
            while (stk.size() > 0) {
                if (stk.top() != spec.front()) {
                    return "No";
                }
                spec.pop_front();
                stk.pop();
            }
        }
    }

    return "Yes";
}

vector<string> calc_output(Input in) {
    vector<string> out(in.train_specs.size(), "");
    for (int i = 0; i < in.train_specs.size(); i++) {
        out[i] = is_train_valid(in.train_specs[i], in.train_size);
    }
    return out;
}

int main() {
    auto in = read_input();
    auto out = calc_output(in);
    for (auto& s : out) {
        cout << s << endl;
    }
}