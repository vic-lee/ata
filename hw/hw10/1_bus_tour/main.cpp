#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

template <typename InIt, typename Predicate, typename UnaryFunction>
UnaryFunction for_each_if(InIt first, InIt last, UnaryFunction fn,
                          Predicate pr) {
    for (; first != last; ++first) {
        if (pr(*first)) fn(*first);
    }
    return fn;
}

struct Input {
    vector<int> niceness;
};

Input read_in() {
    Input in;
    UIN   N;
    cin >> N;
    in.niceness = vector<int>(N - 1, 0);
    for (size_t i = 0; i < (N - 1); i++) cin >> in.niceness[i];
    return in;
}

struct Entry {
    LL     max;
    size_t beg;
    size_t end;

    bool operator<(const Entry& other) const {
        if (max > other.max) {
            return false;
        } else if (max < other.max) {
            return true;
        } else {
            const size_t self_len  = end - beg,
                         other_len = other.end - other.beg;
            if (self_len > other_len) {
                return false;
            } else if (self_len < other_len) {
                return true;
            } else {
                return beg > other.beg;
            }
        }
    }
};

Entry process(const Input& in) {
    priority_queue<Entry> entries;
    Entry                 prev_entry = {LLONG_MIN, 0, 0};

    for (size_t i = 0; i < in.niceness.size(); i++) {
        Entry curr;

        if (prev_entry.max < 0) {
            curr = {in.niceness[i], i, i};
        } else {
            curr = {in.niceness[i] + prev_entry.max, prev_entry.beg, i};
        }

        entries.push(curr);
        prev_entry = curr;
    }

    return entries.top();
}

void fmtout(const Entry& res) {
    if (res.max <= 0) {
        cout << "Yet another overrated tourist destination" << endl;
    } else {
        printf("The nicest part of Y1 is between stop %zu and %zu\n",
               res.beg + 1, res.end + 2);
        // printf(
        //     "The nicest part of Y1 is between stop %zu and %zu with sum
        //     %lld\n", res.beg + 1, res.end + 2, res.max);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = process(in);
    fmtout(out);
}
