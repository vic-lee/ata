#pragma once

#include <unordered_set>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;

namespace ds {

class Graph {
   public:
    Graph(UIN size);

    /// Represents infinity in path distance optimization contexts.
    static const LL DIST_INFTY;

    /// Represents uninitialized vertex ID entry.
    static const UIN VERTEX_ID_UNDEF;

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
     * Searches for all the vertices that are reachable from `src`.
     *
     * @note
     * Performs DFS internally.
     *
     * @param src ID of the vertex from which the DFS begins.
     * @param visited output param. A boolean vector of at least the Graph's
     *      size, initialized to all `false`. On return, all vertices reachable
     *      from `src` will be marked as `true`.
     */
    void find_all_reachables(UIN src, vector<bool>& visited) const;

    struct SSSPOutput {
        /// Initialize by providing the size of the Graph.
        SSSPOutput(size_t sz);

        vector<LL>  dist;
        vector<UIN> pred;
    };

    struct SSSPConfig {
        SSSPConfig() : track_predecessors(true) {}

        /**
         * Whether to keep track of the actual shortest path, in the form
         * of a predecessor list. Defaults to `true`.
         */
        bool track_predecessors;
    };

    /**
     * Performs single source shortest path calculations on the Graph.
     *
     * @note
     * Uses Bellman-Ford if the Graph contains any negative edge(s),
     * or Dijkstra otherwise.
     *
     * @param src the starting vertex for finding the shortest paths.
     * @param config optionally configure the function's behavior. Refer to
     *      SSSPConfig for available options and default values.
     *
     * @return an SSSPOutput struct. @see SSSPOutput.
     */
    SSSPOutput sssp(UIN src, SSSPConfig config = SSSPConfig());

    /// The number of vertices of this Graph.
    size_t size() const { return nodes_.size(); }

    /// The number of edges of this graph.
    size_t num_edges() const { return edges_.size(); }

   private:
    struct Edge {
        UIN u;
        UIN v;
        LL  weight;
    };

    struct Neighbor {
        UIN id;
        LL  edge_weight;
    };

    vector<UIN>              nodes_;
    vector<Edge>             edges_;
    vector<vector<Neighbor>> adj_;

    /// `true` if any of the edges added has a negative weight.
    bool has_negative_edge_;

    /**
     * @idempotent
     * @internal
     * Implementation of the Dijkstra SSSP algorithm.
     *
     * Used only for graphs w/ no negative edges.
     * See `sssp` for argument and return type documentation.
     */
    SSSPOutput sssp_dijkstra(UIN src, const SSSPConfig& config) const;
};

};  // namespace ds