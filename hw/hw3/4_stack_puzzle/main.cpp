#include <deque>
#include <iostream>
#include <stack>

using namespace std;

void output(deque<deque<char>> out) {
    cout << "[" << endl;
    for (auto& o : out) {
        for (auto& e : o) {
            cout << e << " ";
        }
        cout << endl;
    }
    cout << "]" << endl;
}

deque<deque<char>> transform(const deque<char>& src,
                             const deque<char>& dest,
                             int src_ptr,
                             int dest_ptr,
                             stack<char> stk) {
    const bool is_src_exhausted = src_ptr >= src.size();
    const bool is_dest_exhausted = dest_ptr >= dest.size();
    const bool is_stack_exhausted = stk.empty();
    deque<deque<char>> ans;

    if ((is_dest_exhausted || is_src_exhausted) && !is_stack_exhausted) {
        auto k = stk.top();
        printf("Popping %c (srcptr: %d, destptr: %d, stksize: %lu)\n", k,
               src_ptr, dest_ptr, stk.size());
        stk.pop();
        ans = transform(src, dest, src_ptr, dest_ptr, stk);
        for (auto& a : ans) {
            a.push_front('o');
        }
        return ans;
    }

    if (!is_dest_exhausted && !is_src_exhausted) {
        if (src[src_ptr] == dest[dest_ptr]) {
            printf(
                "Found matching chars: %c (srcptr: %d, destptr: %d, stksize: "
                "%lu)\n",
                src[src_ptr], src_ptr, dest_ptr, stk.size());

            auto v1 = transform(src, dest, ++src_ptr, ++dest_ptr, stk);
            for (auto& v : v1) {
                v.push_front('o');
                v.push_front('i');
            }
            stk.push(src[src_ptr]);
            auto v2 = transform(src, dest, ++src_ptr, dest_ptr, stk);
            for (auto& v : v2)
                v.push_back('i');
            for (auto& v : v1)
                ans.push_back(v);
            for (auto& v : v2)
                ans.push_back(v);
            return ans;
        } else {
            printf("Pushing %c (srcptr: %d, destptr: %d, stksize: %lu)\n",
                   src[src_ptr], src_ptr, dest_ptr, stk.size());
            stk.push(src[src_ptr]);
            ans = transform(src, dest, ++src_ptr, dest_ptr, stk);
            for (auto& v : ans)
                v.push_back('i');
            cout << endl;
            output(ans);
            cout << endl;
            return ans;
        }
    }

    return ans;
}

int main() {
    string from, to;
    getline(cin, from);
    getline(cin, to);
    deque<char> src(from.begin(), from.end());
    deque<char> dest(to.begin(), to.end());

    stack<char> stk;
    deque<deque<char>> out;
    if (src.size() == dest.size()) {
        out = transform(src, dest, 0, 0, stk);
    }

    output(out);
}
