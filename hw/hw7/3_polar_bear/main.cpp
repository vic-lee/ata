#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

// #define DEBUG 1

using namespace std;
using UIN = unsigned int;
using Elevation = vector<vector<UIN>>;

class DisjointSet {
    /* map object ID to set ID */
    map<unsigned int, int> roots_;
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
        if (!is_valid(x))
            validate_singular_set(x);
        if (!is_valid(y))
            validate_singular_set(y);

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

    /** Invalidate a set with one element, given its root ID. */
    void invalidate_singular_set(unsigned int rt) {
        if (roots_[rt] == rt) {
            roots_[rt] = -1; /* invalidate element */
            set_cnt_--;      /* ensure this is only performed once */
        }
    }

    /** Invalidate a set with one element, given its root ID. */
    void validate_singular_set(unsigned int rt) {
        if (roots_[rt] == -1) {
            roots_[rt] = rt;
            set_cnt_++;
        }
    }

    bool is_valid(unsigned int rt) { return roots_[rt] != -1; }

    /** The number of sets in this Disjoint Set. */
    unsigned int set_count() const { return set_cnt_; }
};

tuple<Elevation, vector<UIN>> read_in() {
    UIN N, M, x, levels_cnt;
    cin >> N >> M;
    Elevation grid(N, vector<UIN>(M, 0));

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            cin >> x;
            grid[i][j] = x;
        }
    }

    cin >> levels_cnt;
    vector<UIN> levels(levels_cnt, 0);
    for (size_t i = 0; i < levels_cnt; i++) {
        cin >> x;
        levels[i] = x;
    }

    return {grid, levels};
}

inline bool has_right_neighbor(size_t j, UIN M) {
    return j < M - 1;
}

inline bool has_left_neighbor(size_t j) {
    return j >= 1;
}

inline bool has_top_neighbor(size_t i) {
    return i >= 1;
}

inline bool has_down_neighbor(size_t i, UIN N) {
    return i < N - 1;
}

inline size_t coor_to_id(size_t i, size_t j, UIN M) {
    return i * M + j;
}

void debug_union(size_t xi, size_t xj, size_t yi, size_t yj, size_t set_cnt) {
    cout << "merging <" << xi << ", " << xj << "> with <" << yi << ", " << yj
         << ">; set count is " << set_cnt << "\n";
}

vector<UIN> count_islands(Elevation& elevation, vector<UIN> levels) {
    vector<UIN> results(levels.size(), 0);

    size_t N = elevation.size(), M = elevation[0].size();
    auto ds = DisjointSet(N * M);

    for (int l = levels.size() - 1; l >= 0; l--) {
        auto level = levels[l];

#ifdef DEBUG
        cout << "checking distance " << level << "\n";
#endif

        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                auto cur = elevation[i][j];
                UIN self_id = coor_to_id(i, j, M);
                if (cur > level) {
                    ds.validate_singular_set(self_id);
                    if (has_top_neighbor(i) && elevation[i - 1][j] > level) {
                        ds.perform_union(self_id, coor_to_id(i - 1, j, M));
#ifdef DEBUG
                        debug_union(i, j, i - 1, j, ds.set_count());
#endif
                    }
                    if (has_left_neighbor(j) && elevation[i][j - 1] > level) {
                        ds.perform_union(self_id, coor_to_id(i, j - 1, M));
#ifdef DEBUG
                        debug_union(i, j, i, j - 1, ds.set_count());
#endif
                    }
                    if (has_right_neighbor(j, M) &&
                        elevation[i][j + 1] > level) {
                        ds.perform_union(self_id, coor_to_id(i, j + 1, M));

#ifdef DEBUG
                        debug_union(i, j, i, j + 1, ds.set_count());
#endif
                    }
                    if (has_down_neighbor(i, N) &&
                        elevation[i + 1][j] > level) {
                        ds.perform_union(self_id, coor_to_id(i + 1, j, M));
#ifdef DEBUG
                        debug_union(i, j, i + 1, j, ds.set_count());
#endif
                    }
                } else {
                    ds.invalidate_singular_set(self_id);
                }
            }
        }
#ifdef DEBUG
        cout << "set count is " << ds.set_count() << "\n";
#endif
        results[l] = ds.set_count();
    }

    return results;
}

int main() {
    auto [elevation, levels] = read_in();
    auto res = count_islands(elevation, levels);

    ostringstream oss;
    oss << res[0];
    for (size_t i = 0; i < res.size(); i++)
        oss << ' ' << res[i];

    cout << oss.str() << endl;
}
