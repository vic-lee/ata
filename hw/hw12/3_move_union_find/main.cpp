#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using UIN = unsigned int;
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

class DisjointSet {
    /* map object ID to set ID */
    unordered_map<unsigned int, unsigned int> parent_;
    /* number of elements in each set */
    vector<unsigned int> size_;
    /* sum of all the elements' values in each set */
    vector<ULL> sums_;
    /* number of sets in this disjoint set */
    unsigned int set_cnt_ = 0;

   public:
    /**
     * Organize discrete elements into disjoint sets.
     * @param sz: the total number of elements to be considered. Elements' IDs
     *  are initialized to be [0 ... sz-1].
     */
    DisjointSet(unsigned int sz) {
        set_cnt_ = sz;
        size_    = vector<unsigned int>(sz + 1, 1);
        sums_    = vector<ULL>(sz + 1, 0);
        for (unsigned int i = 0; i < sz + 1; i++) {
            parent_[i] = i;
            sums_[i]   = i;
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
        unsigned int x_root = find_set(x);
        unsigned int y_root = find_set(y);

        if (x_root == y_root) return;

        /* merge the smaller set into the larger set. */
        if (size_[x_root] < size_[y_root]) swap(x_root, y_root);
        parent_[y_root] = x_root;
        size_[x_root] += size_[y_root];
        sums_[x_root] += sums_[y_root];

        // perform flattening during union
        // if y is a root element, then it's possible other elements point
        // to y rather than the new root. We perform the flattening now.
        if (y_root == y && size_[y_root] > 1) {
            for (size_t i = 0; i < parent_.size(); i++) {
                if (parent_[i] == y_root) {
                    parent_[i] = x_root;
                }
            }
        }

        set_cnt_--;
    }

    /** Given 2 elements, move `from` to the set that contains `to` */
    void move_set(unsigned int from, unsigned int to) {
        unsigned int from_rt = find_set(from);
        unsigned int to_rt   = find_set(to);

        if (from_rt == to_rt) return;

        parent_[from] = to_rt;

        size_[to_rt]++;
        sums_[to_rt] += from;

        // if we're moving a root node and there are other elements
        // pointing to this node
        if (from == from_rt && size_[from_rt] >= 2) {
            UIN new_parent = parent_.size() + 1;

            // delete all references to `from`, if exists
            for (size_t i = 0; i < parent_.size(); i++) {
                if (parent_[i] == from_rt) {
                    // set the first elem that uses `from` as parent as
                    // the new parent
                    if (new_parent > parent_.size()) {
                        new_parent = i;
                    }
                    parent_[i] = new_parent;
                }
            }

            if (new_parent <= parent_.size()) {
                size_[new_parent] = size_[from_rt] - 1;
                sums_[new_parent] = sums_[from_rt] - from;
            }
        } else {
            size_[from_rt]--;
            sums_[from_rt] -= from;
        }
    }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }

    unsigned int set_size(unsigned int elem) {
        auto set_id = find_set(elem);
        return size_[set_id];
    }

    ULL set_sum(unsigned int elem) {
        auto set_id = find_set(elem);
        return sums_[set_id];
    }
};

struct Cmd {
    int cmd;
    int a;
    int b;
};

struct Input {
    UIN         num_elems;
    vector<Cmd> commands;
};

Input read_in() {
    Input in;

    UIN num_commands;
    cin >> in.num_elems >> num_commands;
    in.commands = vector<Cmd>(num_commands, {-1, -1, -1});
    for (size_t i = 0; i < num_commands; i++) {
        cin >> in.commands[i].cmd;
        if (in.commands[i].cmd == 3) {
            cin >> in.commands[i].a;
        } else {
            cin >> in.commands[i].a >> in.commands[i].b;
        }
    }
    return in;
}

void process(Input& in) {
    auto ds = DisjointSet(in.num_elems);
    for (auto const& command : in.commands) {
        switch (command.cmd) {
            case 1:  // union sets
                ds.union_sets(command.a, command.b);
                break;
            case 2:  // move set
                ds.move_set(command.a, command.b);
                break;
            case 3:  // return number of elements and the sum of elements
                cout << ds.set_size(command.a) << ' ' << ds.set_sum(command.a)
                     << endl;
                break;
            default:
                break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
