#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

enum Operation {
    Push,
    Pop,
};

struct Action {
    Operation op;
    unsigned int x;
    Action(Operation op, unsigned int x) : op(op), x(x){};
};

vector<Action> read_in() {
    unsigned int input_sz, op, x;
    cin >> input_sz;
    vector<Action> dq;
    for (size_t i = 0; i < input_sz; i++) {
        cin >> op >> x;
        dq.emplace_back(op == 1 ? Push : Pop, x);
    }
    return dq;
}

ostringstream simulate_stack(const vector<Action>& actions) {
    ostringstream oss;
    stack<unsigned int> stk;
    for (const auto& action : actions) {
        if (action.op == Push) {
            stk.push(action.x);
        } else {
            if (stk.empty()) {
                return oss;
            }
            oss << stk.top() << ' ';
            stk.pop();
        }
    }
    return oss;
}

ostringstream simulate_queue(const vector<Action>& actions) {
    ostringstream oss;
    queue<unsigned int> q;
    for (auto const action : actions) {
        if (action.op == Push) {
            q.push(action.x);
        } else {
            if (q.empty()) {
                return oss;
            }
            oss << q.front() << ' ';
            q.pop();
        }
    }
    return oss;
}

ostringstream simulate_pqueue(const vector<Action>& actions) {
    ostringstream oss;
    priority_queue<unsigned int> pq;
    for (auto const action : actions) {
        if (action.op == Push) {
            pq.push(action.x);
        } else {
            if (pq.empty()) {
                return oss;
            }
            oss << pq.top() << ' ';
            pq.pop();
        }
    }
    return oss;
}

ostringstream simulate_out(const vector<Action>& actions) {
    ostringstream oss;
    for (auto const action : actions) {
        if (action.op == Pop) {
            oss << action.x << ' ';
        }
    }
    return oss;
}

inline short match_output(string src,
                          string other,
                          string wcontent,
                          ostringstream& oss,
                          short cnt) {
    if (src == other) {
        oss << wcontent << '\n';
        return cnt + 1;
    }
    return cnt;
}

void construct_output(const vector<Action>& actions) {
    string out = simulate_out(actions).str();
    string stk_out = simulate_stack(actions).str();
    string queue_out = simulate_queue(actions).str();
    string pqueue_out = simulate_pqueue(actions).str();

    short match_cnt = 0;
    ostringstream oss;
    match_cnt = match_output(out, stk_out, "stack", oss, match_cnt);
    match_cnt = match_output(out, queue_out, "queue", oss, match_cnt);
    match_cnt = match_output(out, pqueue_out, "priority queue", oss, match_cnt);

    switch (match_cnt) {
        case 1:
            cout << oss.str();
            break;
        case 0:
            cout << "impossible" << endl;
            break;
        default:
            cout << "not sure" << endl;
            break;
    }
}

int main() {
    auto in = read_in();
    construct_output(in);
}
