#pragma once

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
    Graph(UIN size);

    /**
     * Creates a new edge in the graph.
     *
     * @param u the ID of one of the two vertices this edge is connecting
     * @param v the other ID of one of the two vertices this edge is connecting
     * @param w optionally specify the weight of this edge. Negative edge weight
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
     *      size, initialized to all `false`. On return, all vertices reachable
     *      from `src` will be marked as `true`.
     */
    void dfs(UIN src, vector<bool>& visited) const;

    /// The number of vertices of this Graph.
    size_t size() const { return nodes_.size(); }

    /// The number of edges of this graph.
    size_t num_edges() const { return edges_.size(); }
};