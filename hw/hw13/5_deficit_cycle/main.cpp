#include <climits>
#include <iostream>
#include <sstream>
#include <unordered_set>
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

    vector<UIN>                nodes_;
    vector<unordered_set<UIN>> adj_;
    vector<Edge>               edges_;

   public:
    Graph(UIN size);

    /**
     * Creates a new edge in the graph.
     *
     * @param u the ID of one of the two vertices this edge is connecting
     * @param v the other ID of one of the two vertices this edge is
     connecting
     * @param w optionally specify the weight of this edge. Negative edge
     weight
     *      allowed. If not specified, edge weight defaults to `0`.
     */
    void add_edge(UIN u, UIN v, LL w = 0);

    /**
     * @idempotent
     * Determines of a graph as negative cycle(s).
     *
     * @return `true` if the graph has one or more negative cycles, otherwise
     *      `false`.
     */
    bool has_negative_cycle() const;

    /**
     * @idempotent
     * Performs DFS to determine all vertices reachable from `src`.
     *
     * @param src ID of the vertex from which the DFS begins.
     * @param visited output param. A boolean vector of at least the Graph's
     *      size, initialized to all `false`. On return, all vertices
     reachable
     *      from `src` will be marked as `true`.
     */
    void dfs(UIN src, vector<bool>& visited);

    /// The number of vertices of this Graph.
    size_t size() const { return nodes_.size(); }

    /// The number of edges of this graph.
    size_t num_edges() const { return edges_.size(); }
};

Graph::Graph(UIN size) {
    nodes_ = vector<UIN>(size, 0);
    adj_   = vector<unordered_set<UIN>>(size);
}

void Graph::add_edge(UIN u, UIN v, LL w) {
    adj_[u].insert(v);
    adj_[v].insert(u);
    edges_.push_back({u, v, w});
}

bool Graph::has_negative_cycle() const {
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

void Graph::dfs(UIN src, vector<bool>& visited) {
    visited[src] = true;
    for (auto const& next_candidate : adj_[src]) {
        if (!visited[next_candidate]) {
            dfs(next_candidate, visited);
        }
    }
}

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
