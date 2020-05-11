#include <unordered_set>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;

class Graph {
    struct Edge {
        UIN u;
        UIN v;
        LL  weight;
    };

    vector<UIN>                nodes_;
    vector<unordered_set<UIN>> adj_;
    vector<Edge>               edges_;

   public:
    Graph(UIN size) {
        nodes_ = vector<UIN>(size, 0);
        adj_   = vector<unordered_set<UIN>>(size);
    }

    void add_edge(UIN u, UIN v, LL w = 0) {
        adj_[u].insert(v);
        adj_[v].insert(u);
        edges_.push_back({u, v, w});
    }

    // Returns true if the graph has negative cycle(s), false otherwise.
    // The function is idempotent.
    bool has_negative_cycle() const {
        const LL NULL_NODE = -1;

        vector<LL> dists(size(), LLONG_MAX);
        vector<LL> predecessors(size(), NULL_NODE);

        size_t src = 0;
        dists[src] = 0;

        // Performs Bellman-Ford relaxation.
        for (size_t repeat_cnt = 0; repeat_cnt < size(); repeat_cnt++) {
            for (auto const& edge : edges_) {
                if (dists[edge.u] + edge.weight < dists[edge.v]) {
                    dists[edge.v]        = dists[edge.u] + edge.weight;
                    predecessors[edge.v] = edge.u;
                }
            }
        }

        // Check if negative cycles exist
        for (auto const& edge : edges_) {
            if (dists[edge.u] + edge.weight < dists[edge.v]) {
                return true;  // found negative cycle
            }
        }

        return false;
    }

    /** Mark all nodes reachable from `src` as visited */
    void dfs(UIN src, vector<bool>& visited) {
        visited[src] = true;
        for (auto const& next_candidate : adj_[src]) {
            if (!visited[next_candidate]) {
                dfs(next_candidate, visited);
            }
        }
    }

    // Returns the number of nodes within this graph.
    size_t size() const { return nodes_.size(); }
};
