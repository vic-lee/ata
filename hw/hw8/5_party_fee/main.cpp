#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using UIN = unsigned int;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << ' ';
    }
    cout << oss.str();
}

class DisjointSet {
    /* map object ID to set ID */
    map<unsigned int, unsigned int> parent_;
    vector<unsigned int> size_;
    vector<int> balance_;
    unsigned int set_cnt_ = 0;

   public:
    /**
     * Organize discrete elements into disjoint sets.
     * @param sz: the total number of elements to be considered. Elements' IDs
     *  are initialized to be [0 ... sz-1].
     */
    DisjointSet(unsigned int sz, const vector<int> balance) {
        set_cnt_ = sz;
        size_ = vector<unsigned int>(sz, 1);
        balance_ = vector<int>(sz, 0);
        for (unsigned int i = 0; i < sz; i++) {
            parent_[i] = i;
            balance_[i] = balance[i];
        }
    }

    /** Find the Set ID of an element, given its ID. */
    unsigned int find_set(unsigned int x) {
        if (parent_[x] == x) {
            return parent_[x];
        }
        return parent_[x] = find_set(parent_[x]);
    }

    /** Given 2 elements, union the sets that they belong to. */
    void union_sets(unsigned int x, unsigned int y) {
        unsigned int a = find_set(x);
        unsigned int b = find_set(y);

        if (a == b) return;

        /* merge the smaller set into the larger set. */
        if (size_[a] < size_[b]) swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        balance_[a] += balance_[b];
        balance_[b] = 0;
        set_cnt_--;
    }

    vector<int> balance() const { return balance_; }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }

    /**
     * Returns a snapshot of the disjoint set, a map with the parent IDs as
     * keys and a vector containing object IDs belonging to that set as values.
     */
    unordered_map<UIN, vector<int>> set_snapshot() {
        unordered_map<UIN, vector<int>> snapshot;

        for (auto it = parent_.begin(); it != parent_.end(); it++) {
            auto obj_id = it->first, obj_parent = it->second;

            if (snapshot.find(obj_parent) == snapshot.end())
                snapshot[obj_parent] = vector<int>(1, obj_id);
            else
                snapshot[obj_parent].push_back(obj_id);
        }

        return snapshot;
    }
};

struct Input {
    vector<int> balance;
    vector<tuple<UIN, UIN>> friendships;
};

Input read_in() {
    Input in;
    UIN num_ppl, num_friendships, a, b;
    cin >> num_ppl >> num_friendships;

    in.balance = vector<int>(num_ppl, 0);
    for (size_t i = 0; i < num_ppl; i++) cin >> in.balance[i];

    in.friendships = vector<tuple<UIN, UIN>>(num_friendships);
    for (size_t i = 0; i < num_friendships; i++) {
        cin >> a >> b;
        in.friendships[i] = {a, b};
    }

    return in;
}

bool can_pay_fees(vector<int>& balance, vector<tuple<UIN, UIN>>& friendships) {
    auto ds = DisjointSet(balance.size(), balance);

    for (auto const& friendship : friendships)
        ds.union_sets(get<0>(friendship), get<1>(friendship));

    auto group_balances = ds.balance();

    return find_if(group_balances.begin(), group_balances.end(),
                   [](int& bs) { return bs != 0; }) == group_balances.end();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    if (can_pay_fees(in.balance, in.friendships))
        cout << "POSSIBLE" << endl;
    else
        cout << "IMPOSSIBLE" << endl;
}
