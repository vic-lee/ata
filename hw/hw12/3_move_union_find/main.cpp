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
    vector<unsigned int>                      size_;
    vector<unsigned int>                      sums_;
    unsigned int                              set_cnt_ = 0;

   public:
    /**
     * Organize discrete elements into disjoint sets.
     * @param sz: the total number of elements to be considered. Elements' IDs
     *  are initialized to be [0 ... sz-1].
     */
    DisjointSet(unsigned int sz) {
        set_cnt_ = sz;
        size_    = vector<unsigned int>(sz + 1, 1);
        sums_    = vector<unsigned int>(sz + 1, 0);
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
        unsigned int a = find_set(x);
        unsigned int b = find_set(y);

        if (a == b) return;

        /* merge the smaller set into the larger set. */
        if (size_[a] < size_[b]) swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        sums_[a] += sums_[b];
        set_cnt_--;
    }

    /** Given 2 elements, move `from` to the set that contains `to` */
    void move_set(unsigned int from, unsigned int to) {
        unsigned int from_rt = find_set(from);
        unsigned int to_rt   = find_set(to);

        // cout << "parent of " << from << " is " << from_rt << "; parent of "
        //  << to << " is " << to_rt << endl;

        if (from_rt == to_rt) return;

        // cout << "moving " << from << " (root: " << from_rt << ") to " << to
        //  << " (root: " << to_rt << ")" << endl;

        parent_[from] = to_rt;

        size_[to_rt]++;
        size_[from_rt]--;
        sums_[to_rt] += from;
        sums_[from_rt] -= from;

        if (from == from_rt && size_[from_rt] >= 1) {
            UIN new_parent = parent_.size() + 1;

            // delete all references to `from`, if exists
            for (size_t i = 0; i < parent_.size(); i++) {
                if (parent_[i] == from) {
                    // set the first elem that uses `from` as parent as
                    // the new parent
                    if (new_parent > parent_.size()) {
                        new_parent = i;
                    }
                    parent_[i] = new_parent;
                }
            }

            // if a new parent is set, transfer size_ and sums_ values
            if (new_parent <= parent_.size()) {
                size_[new_parent] = size_[from_rt];
                sums_[new_parent] = sums_[from_rt];
            }
        }

        // cout << "parent of " << from << " becomes " << find_set(from) <<
        // endl; cout << "sum becomes " << sums_[to_rt] << endl;
    }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }

    unsigned int set_size(unsigned int elem) {
        auto set_id = find_set(elem);
        return size_[set_id];
    }

    unsigned int set_sum(unsigned int elem) {
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
        // cout << command.cmd << " " << command.a << " " << command.b << endl;
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
