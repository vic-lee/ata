#include <deque>
#include <iostream>
#include <stack>

using namespace std;

deque<char> read_in() {
    deque<char> in;
    string line;
    while (getline(cin, line) && !line.empty())
        in.push_back(line.at(0));
    return in;
}

/** Returns if operator x has lower or equal precedence than operator y */
bool has_lower_or_eq_precedence(char x, char y) {
    const string high = "*/", low = "+-";
    return ((low.find(x) != string::npos && high.find(y) != string::npos) ||
            (high.find(x) != string::npos && high.find(y) != string::npos) ||
            (low.find(x) != string::npos && low.find(y) != string::npos));
}

bool is_operator(char s) {
    const string ops = "+-*/";
    return ops.find(s) != string::npos;
}

deque<char> in_to_post(deque<char> in) {
    deque<char> res;
    stack<char> ops;

    for (auto& t : in) {
        if (t == '(') {
            ops.push(t);
        } else if (t == ')') {
            while (ops.size() > 0) {
                if (ops.top() != '(') {
                    res.push_back(ops.top());
                    ops.pop();
                } else {
                    ops.pop();
                    break;
                }
            }
        } else if (is_operator(t)) {
            while (ops.size() > 0 && ops.top() != '(' &&
                   has_lower_or_eq_precedence(t, ops.top())) {
                res.push_back(ops.top());
                ops.pop();
            }
            ops.push(t);
        } else {
            res.push_back(t);
        }
    }

    while (!ops.empty()) {
        res.push_back(ops.top());
        ops.pop();
    }

    return res;
}

int main() {
    auto in = read_in();
    auto post = in_to_post(in);
    const string s(post.begin(), post.end());
    cout << s << endl;
}
