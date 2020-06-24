#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Coordinate {
    unsigned int id;
    double x;
    double y;
    Coordinate(unsigned int id, double x, double y) : id(id), x(x), y(y) {}
};

ostream& operator<<(ostream& os, const Coordinate& coor) {
    os << "(" << coor.id << ": <" << coor.x << ", " << coor.y << ">)";
    return os;
};

bool operator==(const Coordinate& c1, const Coordinate& c2) {
    return c1.x == c2.x && c1.y == c2.y;
}

inline double eucl_dist(const Coordinate& c1, const Coordinate& c2) {
    return sqrt(pow((c1.x - c2.x), 2) + pow((c1.y - c2.y), 2));
}

class DisjointSet {
    /* map object ID to set ID */
    map<unsigned int, unsigned int> roots_;
    vector<unsigned int> ranks_;
    unsigned int set_cnt_ = 0;

   public:
    /**
     * Organize discrete elements into disjoint sets.
     * @param sz: the total number of elements to be considered. Elements' IDs
     *  are initialized to be [0 ... sz-1].
     */
    DisjointSet(unsigned int sz) {
        set_cnt_ = sz;
        ranks_ = vector<unsigned int>(sz, 1);
        for (unsigned int i = 0; i < sz; i++) {
            roots_[i] = i;
        }
    }

    /** Find the Set ID of an element, given its ID. */
    unsigned int find(unsigned int x) {
        if (roots_[x] != x) {
            roots_[x] = find(roots_[x]); /* eagerly flatten tree */
        }
        return roots_[x];
    }

    /** Given 2 elements, union the sets that they belong to. */
    void perform_union(unsigned int x, unsigned int y) {
        unsigned int x_set_rt = find(x);
        unsigned int y_set_rt = find(y);

        if (x_set_rt == y_set_rt)
            return;

        /* merge the smaller set into the larger set. */
        if (ranks_[x_set_rt] < ranks_[y_set_rt]) {
            roots_[x_set_rt] = y_set_rt;
        } else if (ranks_[x_set_rt] > ranks_[y_set_rt]) {
            roots_[y_set_rt] = x_set_rt;
        } else {
            roots_[y_set_rt] = x_set_rt;
            ranks_[x_set_rt]++; /* break ties between ranks */
        }
        set_cnt_--;
    }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }
};

tuple<double, vector<Coordinate>> read_in() {
    unsigned int N;
    double D, x, y;
    cin >> N >> D;
    vector<Coordinate> coors;
    for (size_t i = 0; i < N; i++) {
        cin >> x >> y;
        coors.emplace_back(i, x, y);
    }

    return {D, coors};
}

/**
 * Find the number of constellations among the stars.
 *
 * Two stars are said to be in a constellation if their euclidean distance
 * is less than or equal to D.
 *
 * @param D the distance within which 2 stars are considered to be in the same
 *  constellation.
 * @param coors coordinates of the stars.
 */
unsigned int count_constellations(const double D,
                                  const vector<Coordinate>& coors) {
    auto ds = DisjointSet(coors.size());

    for (size_t i = 0; i < coors.size(); i++) {
        for (size_t j = i + 1; j < coors.size(); j++) {
            if (eucl_dist(coors[i], coors[j]) <= D) {
                ds.perform_union(i, j);
            }
        }
    }

    return ds.set_count();
}

int main() {
    auto [D, coors] = read_in();
    cout << count_constellations(D, coors);
}
