#include "graph.hpp"

#include <climits>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using UIN = unsigned int;
using LL  = long long;

namespace ds {

const LL  Graph::DIST_INFTY      = UINT_MAX;
const UIN Graph::VERTEX_ID_UNDEF = UINT_MAX;

Graph::Graph(UIN size, GraphConfig config) : config_(config) {
    nodes_             = std::vector<UIN>(size, 0);
    adj_               = std::vector<std::vector<Neighbor>>(size);
    has_negative_edge_ = false;
}

void Graph::add_edge(UIN u, UIN v, LL w) {
    const LL edge_weight = this->weighted() ? w : 0;

    if (this->directed()) {
        adj_[u].emplace_back(v, edge_weight);
        edges_.emplace_back(u, v, edge_weight);
    } else {
        adj_[u].emplace_back(v, edge_weight);
        adj_[v].emplace_back(u, edge_weight);
        edges_.emplace_back(u, v, edge_weight);
        edges_.emplace_back(v, u, edge_weight);
    }

    if (edge_weight < 0) {
        has_negative_edge_ = true;
    }
}

bool Graph::has_negative_cycle() const {
    auto out = sssp_bellman_ford(0, SSSPConfig());

    // Check if negative cycles exist
    for (auto const& edge : edges_) {
        if (out.dist[edge.u] + edge.weight < out.dist[edge.v]) {
            return true;  // found negative cycle
        }
    }

    return false;
}

bool Graph::is_bipartite() const {
    // Algorithm:
    // A graph is bipartite iff it is two-colorable.
    // (Another theorem is that a graph is bipartite iff it does not contain
    // cycles of odd-length (odd cycles), but that is more difficult to
    // implement as an algorihtm.)
    // Therefore, we attempt to 2-colorize the graph in a modified BFS.

    LL const PARTITION_UNSET = -1;
    bool     is_bipartite    = true;

    auto partition = std::vector<int>(size(), PARTITION_UNSET);

    std::queue<UIN> queue;

    for (size_t start_vtx = 0; start_vtx < size(); start_vtx++) {
        // attempt all vertices as starting points to ensure all vertices are
        // visited, as the graph may not be connected.

        if (partition[start_vtx] == PARTITION_UNSET) {
            partition[start_vtx] = 0;
            queue.push(start_vtx);
            while (!queue.empty()) {
                UIN u = queue.front();
                queue.pop();

                for (auto const& neighbor : adj_[u]) {
                    UIN v = neighbor.id;
                    if (partition[v] == PARTITION_UNSET) {
                        // Assign to the neighbor the partition that is opposite
                        // to the current vertex's.
                        partition[v] = !partition[u];
                        queue.push(v);
                    } else {  // if the neighbor has an assigned partition
                        // Graph continues to be bipartite if it is currently
                        // bipartite and current vertex's partition differs from
                        // its neighbor's.
                        is_bipartite &= partition[v] != partition[u];
                    }
                }
            }
        }
    }

    return is_bipartite;
}

bool Graph::is_connected() const {
    // Algorithm:
    // A graph is only connected if one graph traversal can reach all the
    // vertices in the graph. If certain vertices are only reachable by multiple
    // graph traversals, then we have shown that there exists vertices that are
    // not reachable from the starting vertex of the prior traversal.
    //
    // Here we opt for DFS as the traversal method, but BFS also works.
    // A graph with 0 vertices is trivially connected.

    if (size() == 0) return true;

    std::vector<bool> visited(size(), false);
    UIN               visit_count = 0;

    std::function<void(size_t)> dfs_connected = [&](size_t src) {
        visited[src] = true;
        visit_count++;
        for (auto const& neighbor : this->adj_[src]) {
            auto const candidate = neighbor.id;
            if (!visited[candidate]) {
                dfs_connected(candidate);
            }
        }
    };

    dfs_connected(0);

    return visit_count == size();
}

bool Graph::is_a_tree() const {
    bool is_a_tree = false;
    return is_a_tree;
}

void Graph::find_all_reachables(UIN src, std::vector<bool>& visited) const {
    visited[src] = true;
    for (auto const& edge : adj_[src]) {
        auto next_candidate = edge.id;
        if (!visited[next_candidate]) {
            find_all_reachables(next_candidate, visited);
        }
    }
}

Graph::SSSPOutput::SSSPOutput(size_t sz)
    : dist(std::vector<LL>(sz, Graph::DIST_INFTY)),
      pred(std::vector<UIN>(sz, Graph::VERTEX_ID_UNDEF)) {}

Graph::SSSPOutput Graph::sssp(UIN src, SSSPConfig config) const {
    if (!has_negative_edge_) {
        return sssp_dijkstra(src, config);
    } else {
        return sssp_bellman_ford(src, config);
    }
}

Graph::SSSPOutput Graph::sssp_dijkstra(UIN               src,
                                       const SSSPConfig& config) const {
    Graph::SSSPOutput out(size());

    // { distance_to_src, vertex_id }
    // Sorts ascendingly by the first element: the element that is closest
    // to the source should be at the front of the queue.
    using QueueEntry = std::pair<LL, UIN>;
    using MinQueue   = std::set<QueueEntry>;

    MinQueue minqueue;

    // The distance to the source is 0.
    out.dist[src] = 0;

    // Put src in the queue to kickstart shortest path calculation.
    minqueue.emplace(out.dist[src], src);

    while (!minqueue.empty()) {
        // Pop the vertex that is unvisited && currently closest to the src.
        auto min_dist_entry = *minqueue.begin();
        minqueue.erase(minqueue.begin());

        // Invariant: we know the distance from src to u is already minimal.
        auto u = min_dist_entry.second;

        // "relax" (shorten) the distance from src to each of `u`'s neighbor
        // by checking if path `src -> ... -> u -> v` is shorter than `v`'s
        // current shortest distance to src as stored in the dist table.

        for (auto const& edge : adj_[u]) {
            auto v   = edge.id;
            LL   alt = out.dist[u] + edge.edge_weight;

            // cout << u << " adjacent to " << v << endl;

            if (alt < out.dist[v]) {
                // if `src -> ... -> u -> v` is indeed shorter,
                // update `v`'s entry in the queue so that its distance to
                // src reflects the new, shortest distance.

                minqueue.erase(std::make_pair(out.dist[v], v));
                out.dist[v] = alt;
                out.pred[v] = u;
                minqueue.emplace(out.dist[v], v);
            }
        }
    }

    return out;
}

Graph::SSSPOutput Graph::sssp_bellman_ford(UIN               src,
                                           const SSSPConfig& config) const {
    auto out = Graph::SSSPOutput(this->size());

    FOR_N(this->size()) {
        for (auto const& edge : edges_) {
            if (out.dist[edge.u] + edge.weight < out.dist[edge.v]) {
                out.dist[edge.v] = out.dist[edge.u] + edge.weight;
                if (config.track_predecessors) {
                    out.pred[edge.v] = edge.u;
                }
            }
        }
    }

    return out;
}

Graph::APSPOutput::APSPOutput(size_t vertex_count) {
    dist = std::vector<std::vector<LL>>(
        vertex_count, std::vector<LL>(vertex_count, Graph::DIST_INFTY));

    next = std::vector<std::vector<UIN>>(
        vertex_count, std::vector<UIN>(vertex_count, Graph::VERTEX_ID_UNDEF));
}

Graph::APSPOutput Graph::apsp() const {
    APSPOutput out(this->size());

    // initializes adjacent vertices' distance and next properties
    for (auto const& edge : edges_) {
        out.dist[edge.u][edge.v] = edge.weight;
        out.next[edge.u][edge.v] = edge.v;
    }

    // initializes properties for paths where start and end is equal
    for (size_t v = 0; v < size(); v++) {
        out.dist[v][v] = 0;
        out.next[v][v] = v;
    }

    // Performs Floyd-Warshall iteratively, gradually expanding the vertex
    // consideration set. This can also be done recursively.
    //
    // Recurrence relation (`SP` stands for shortest path):
    //  SP(i, j, k) = min(
    //      SP(i, j, k-1),
    //      SP(i, k, k-1) + SP(k, j, k-1)
    //  )
    // Expand k to |V| to arrive at the solution to the graph.

    for (size_t alt_vertex = 0; alt_vertex < size(); alt_vertex++) {
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < size(); j++) {
                // Considers both the path that goes through `alt_vertex`
                // and the one that does not.
                auto alt = out.dist[i][alt_vertex] + out.dist[alt_vertex][j];
                if (out.dist[i][j] > alt) {
                    out.dist[i][j] = alt;
                    out.next[i][j] = out.next[i][alt_vertex];
                }
            }
        }
    }
    return out;
}

std::ostringstream Graph::adjacency_list_repr() const {
    std::ostringstream oss;

    for (size_t vertex = 0; vertex < adj_.size(); vertex++) {
        oss << vertex;

        if (adj_[vertex].size()) {
            oss << "\t";
        }

        for (size_t neighbor = 0; neighbor < adj_[vertex].size(); neighbor++) {
            auto const neighbor_id = adj_[vertex][neighbor].id;
            auto const weight      = adj_[vertex][neighbor].edge_weight;

            if (weighted()) {
                oss << "{ " << neighbor_id << ", " << weight << " }";
            } else {
                oss << neighbor_id;
            }

            if (neighbor < adj_[vertex].size()) {
                oss << " ";
            }
        }

        oss << "\n";
    }

    return oss;
}

std::ostringstream Graph::adjacency_matrix_repr() const {
    std::ostringstream oss;

    auto       adj_matrix = adjacency_matrix();
    auto const COL_WIDTH  = 4;

    // render initial row, which is vertex IDs
    oss << std::setw(COL_WIDTH * 2) << 0;
    for (size_t vertex = 1; vertex < size(); vertex++) {
        oss << std::setw(COL_WIDTH) << vertex;
    }
    oss << '\n';

    // render adj matrix, w/ first colum being vertex IDs
    for (size_t from_vtx = 0; from_vtx < adj_matrix.size(); from_vtx++) {
        oss << std::setw(COL_WIDTH) << from_vtx;

        for (size_t to_vertex = 0; to_vertex < adj_matrix[from_vtx].size();
             to_vertex++) {
            oss << std::setw(COL_WIDTH) << adj_matrix[from_vtx][to_vertex];
        }

        oss << '\n';
    }

    return oss;
}

Graph::AdjacencyMatrix Graph::adjacency_matrix() const {
    auto adj_matrix = AdjacencyMatrix(size(), std::vector<bool>(size(), false));

    for (size_t u = 0; u < adj_.size(); u++) {
        for (auto const v : adj_[u]) {
            adj_matrix[u][v.id] = true;
        }
    }

    return adj_matrix;
}

};  // namespace ds