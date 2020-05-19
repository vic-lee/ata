#include <deque>
#include <iostream>
#include <stack>

using namespace std;

struct Result {
    deque<deque<char>> ans;
    bool valid;
};

void fmtout(deque<deque<char>> out) {
    cout << "[" << endl;
    for (auto& o : out) {
        for (auto& e : o) {
            cout << e << " ";
        }
        cout << endl;
    }
    cout << "]" << endl;
}

Result merge_result(Result r1, Result r2) {
    if (!r1.valid && !r2.valid) {
        Result r = {{{' '}}, false};
        return r;
    } else if (r1.valid && !r2.valid) {
        return r1;
    } else if (r2.valid && !r1.valid) {
        return r2;
    } else {
        deque<deque<char>> dq;
        for (auto& v : r1.ans)
            dq.push_back(v);
        for (auto& v : r2.ans)
            dq.push_back(v);
        Result r = {dq, true};
        return r;
    }
}

void prepend_push_and_pop(deque<deque<char>>& dq) {
    for (auto& v : dq) {
        v.push_front('i');
        v.push_front('o');
    }
}

void prepend_push(deque<deque<char>>& dq) {
    for (auto& v : dq)
        v.push_front('i');
}

void prepend_pop(deque<deque<char>>& dq) {
    for (auto& v : dq)
        v.push_front('o');
}

Result transform(const deque<char>& src,
                 const deque<char>& dst,
                 int sptr,
                 int dptr,
                 stack<char> stk) {
    const bool is_src_exhausted = sptr >= src.size();
    const bool is_dest_exhausted = dptr >= dst.size();
    const bool is_stack_exhausted = stk.empty();

    deque<deque<char>> ans = {{' '}};

    if (is_dest_exhausted && is_stack_exhausted && is_src_exhausted) {
        Result r = {ans, true};
        return r;
    }

    if (is_dest_exhausted &&
        (!is_stack_exhausted || !is_src_exhausted)) {  // invalid situation
        Result r = {ans, false};
        return r;
    }

    if (is_src_exhausted && !is_stack_exhausted) {  // pop stack and fail
        if (stk.top() != dst[dptr]) {
            Result r = {ans, false};
            return r;
        } else {
            auto k = stk.top();
            stk.pop();
            printf("Popped %c (srcptr: %d, destptr: %d, stksize: %lu)\n", k,
                   sptr, dptr, stk.size());

            auto rsp = transform(src, dst, sptr, ++dptr, stk);
            if (rsp.valid)
                prepend_pop(rsp.ans);
            return rsp;
        }
    }
    if (!is_src_exhausted && !is_dest_exhausted) {
        if (src[sptr] == dst[dptr]) {
            printf(
                "Found matching chars: %c (srcptr: %d, destptr: %d, stksize: "
                "%lu)\n",
                src[sptr], sptr, dptr, stk.size());

            // option 1: add that matching character to dest
            printf("Added matching char %c to dest\n", src[sptr]);
            auto rsp1 = transform(src, dst, sptr + 1, dptr + 1, stk);
            if (rsp1.valid) {
                prepend_push_and_pop(rsp1.ans);
            }
            // option 2 : push that character to stack
            stk.push(src[sptr]);
            printf(
                "[Matching char] Pushed %c (srcptr: %d, destptr: %d, stksize:"
                "%lu)\n",
                src[sptr], sptr, dptr, stk.size());

            auto rsp2 = transform(src, dst, sptr + 1, dptr, stk);
            if (rsp2.valid) {
                prepend_push(rsp2.ans);
            }

            return merge_result(rsp1, rsp2);
        } else {
            stk.push(src[sptr]);
            printf("Pushed %c (srcptr: %d, destptr: %d, stksize: %lu)\n",
                   src[sptr], sptr, dptr, stk.size());

            auto rsp = transform(src, dst, ++sptr, dptr, stk);
            if (rsp.valid) {
                prepend_push(rsp.ans);
            }
            return rsp;
        }
    }

    Result r = {ans, false};
    return r;
}

int main() {
    string from, to;
    getline(cin, from);
    getline(cin, to);
    deque<char> src(from.begin(), from.end());
    deque<char> dest(to.begin(), to.end());

    Result out;
    stack<char> stk;
    if (src.size() == dest.size()) {
        out = transform(src, dest, 0, 0, stk);
    }
    fmtout(out.ans);
}
