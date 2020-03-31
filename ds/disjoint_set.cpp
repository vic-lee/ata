#include <map>
#include <vector>

using namespace std;

class DisjointSet {
    /* map object ID to set ID */
    map<unsigned int, unsigned int> parent_;
    vector<unsigned int> size_;
    unsigned int set_cnt_ = 0;

   public:
    /**
     * Organize discrete elements into disjoint sets.
     * @param sz: the total number of elements to be considered. Elements' IDs
     *  are initialized to be [0 ... sz-1].
     */
    DisjointSet(unsigned int sz) {
        set_cnt_ = sz;
        size_ = vector<unsigned int>(sz, 1);
        for (unsigned int i = 0; i < sz; i++)
            parent_[i] = i;
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

        if (a == b)
            return;

        /* merge the smaller set into the larger set. */
        if (size_[a] < size_[b])
            swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        set_cnt_--;
    }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }
};