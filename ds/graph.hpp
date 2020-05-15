#pragma once

#include <unordered_set>
#include <vector>

using UIN = unsigned int;
using LL  = long long;

namespace ds {

class Graph {
   public:
    /// Configures properties of a Graph instance.
    struct GraphConfig {
        bool directed;
        /**
         * Specifies whether edges of this graph have weights.
         * Should be `true` if any of the edges have a weight. The weight could
         * be either positive or negative.
         * Defaults to `false`, i.e. an unweighted graph, if not specified.
         */
        bool weighted;

        GraphConfig() : directed(false), weighted(false) {}
        GraphConfig(bool directed, bool weighted)
            : directed(directed), weighted(weighted) {}
    };

    Graph(UIN size, GraphConfig config = GraphConfig());

    /// Represents infinity in path distance optimization contexts.
    static const LL DIST_INFTY;

    /// Represents uninitialized vertex ID entry.
    static const UIN VERTEX_ID_UNDEF;

    /**
     * Creates a new edge in the graph.
     *
     * @note
     * For an undirected graph, the order of the first and second argument
     * does not matter (i.e. add_edge(1, 2) is equivalent to add_edge(2, 1)).
     * The order of the `u` and `v` arguments matters for a directed graph.
     *
     * @param u the vertex ID of where the edge originates.
     * @param v the vertex ID of where the edge ends.
     * @param w optionally specify the weight of this edge. For this argument to
     *      work, ensure the Graph is configured to be weighted when it is
     *      initialized. Negative edge weight allowed. If the graph is weighted
     *      and this argument is not specified, the edge weight defaults to `0`.
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
    void find_all_reachables(UIN src, std::vector<bool>& visited) const;

    struct SSSPOutput {
        /// Initialize by providing the size of the Graph.
        SSSPOutput(size_t sz);

        std::vector<LL>  dist;
        std::vector<UIN> pred;
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
     * @idempotent
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
    SSSPOutput sssp(UIN src, SSSPConfig config = SSSPConfig()) const;

    /// The number of vertices of this Graph.
    size_t size() const { return nodes_.size(); }

    /// The number of edges of this graph.
    size_t num_edges() const { return edges_.size(); }

    /**
     * Whether the graph is initialized to be a directed graph.
     * Edge directionality is not mutable after graph initialization.
     */
    bool directed() const { return config_.directed; }

    /**
     * Whether the graph's edges are allowed to have weights.
     * This is configured on graph initialization and is not modifiable.
     */
    bool weighted() const { return config_.weighted; }

   private:
    struct Edge {
        UIN u;
        UIN v;
        LL  weight;

        Edge(UIN u, UIN v, LL w) : u(u), v(v), weight(w) {}
    };

    struct Neighbor {
        UIN id;
        LL  edge_weight;

        Neighbor(UIN id, LL w) : id(id), edge_weight(w) {}
    };

    std::vector<UIN>                   nodes_;
    std::vector<Edge>                  edges_;
    std::vector<std::vector<Neighbor>> adj_;
    GraphConfig                        config_;

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

    /**
     * @idempotent
     * @internal
     * Implements the Bellman Ford SSSP algorithm.
     *
     * Used only for graphs w/ negative edges. graphs with only non-negative
     * edges, use Dijkstra for better asymptotic complexity.
     */
    SSSPOutput sssp_bellman_ford(UIN src, const SSSPConfig& config) const;
};

};  // namespace ds