#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

void permute(int i,
             int j,
             stack<char>& stk,
             stringstream& curr_ans,
             deque<char>& dst,
             deque<char>& src,
             stringstream& all_ans) {
    if (j > src.size() - 1) {
        curr_ans << "\n";
        all_ans << curr_ans.str();
        return;
    }

    if (stk.empty() && i < src.size()) {
        stk.push(src[i]);
        cout << "pushed " << src[i] << endl;
        curr_ans << "i ";
        permute(i + 1, j, stk, curr_ans, dst, src, all_ans);
    } else if (!stk.empty()) {
        if (stk.top() == dst[j]) {
            if (i < dst.size()) {
                stack<char> s1 = stk;
                s1.push(src[i]);
                stringstream ss1;
                ss1 << curr_ans.rdbuf();
                ss1 << "i ";
                permute(i + 1, j, s1, ss1, dst, src, all_ans);
            }
            cout << "popped " << stk.top() << endl;
            stk.pop();
            curr_ans << "o ";
            permute(i, j + 1, stk, curr_ans, dst, src, all_ans);
        } else {
            if (i < src.size()) {
                cout << "pushed " << src[i] << endl;
                stk.push(src[i]);
                curr_ans << "i ";
                permute(i + 1, j, stk, curr_ans, dst, src, all_ans);
            } else {
                cout << "bug" << endl;
                return;
            }
        }
    }
}

int main() {
    string from, to;
    getline(cin, from);
    getline(cin, to);

    deque<char> src(from.begin(), from.end());
    deque<char> dst(to.begin(), to.end());

    stack<char> stk;
    stringstream ss, ans;
    if (src.size() == dst.size()) {
        ans << "[\n";
        permute(0, 0, stk, ss, dst, src, ans);
        ans << "]\n";
        cout << ans.str() << endl;
    } else {
        printf("[\n]\n");
    }
}
