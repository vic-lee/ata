#include <climits>
#include <iostream>
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

class Graph {
    struct Edge {
        UIN u;
        UIN v;
        LL  weight;
    };

    vector<UIN>         nodes_;
    vector<vector<UIN>> adj_;
    vector<Edge>        edges_;

   public:
    Graph(UIN size) {
        nodes_ = vector<UIN>(size, 0);
        adj_   = vector<vector<UIN>>(size);
    }

    void add_edge(UIN u, UIN v, LL w = 0) {
        adj_[u].push_back(v);
        adj_[v].push_back(u);
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
        for (size_t i = 0; i < adj_[src].size(); i++) {
            UIN next_candidate = adj_[src][i];
            if (!visited[next_candidate]) {
                dfs(next_candidate, visited);
            }
        }
    }

    // Returns the number of nodes within this graph.
    size_t size() const { return nodes_.size(); }
};

Graph read_in() {
    UIN num_cities, num_highways, u, v;
    int weight;
    cin >> num_cities >> num_highways;
    Graph g(num_cities);

    for (size_t i = 0; i < num_highways; i++) {
        cin >> u >> v >> weight;
        g.add_edge(u, v, weight);
    }

    return g;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto graph = read_in();
    cout << (graph.has_negative_cycle() ? "possible" : "not possible") << endl;
}
