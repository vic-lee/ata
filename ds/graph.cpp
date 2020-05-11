#include "graph.hpp"

#include <climits>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;

namespace ds {

const LL  Graph::DIST_INFTY      = UINT_MAX;
const UIN Graph::VERTEX_ID_UNDEF = UINT_MAX;

Graph::Graph(UIN size) {
    nodes_ = vector<UIN>(size, 0);
    adj_   = vector<vector<Neighbor>>(size);
}

void Graph::add_edge(UIN u, UIN v, LL w) {
    adj_[u].push_back({v, w});
    adj_[v].push_back({u, w});
    edges_.push_back({u, v, w});

    if (w < 0) {
        has_negative_edge_ = true;
    }
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

void Graph::find_all_reachables(UIN src, vector<bool>& visited) const {
    visited[src] = true;
    for (auto const& edge : adj_[src]) {
        auto next_candidate = edge.id;
        if (!visited[next_candidate]) {
            find_all_reachables(next_candidate, visited);
        }
    }
}

Graph::SSSPOutput::SSSPOutput(size_t sz)
    : dist(vector<LL>(sz, Graph::DIST_INFTY)),
      pred(vector<UIN>(sz, Graph::VERTEX_ID_UNDEF)) {}

Graph::SSSPOutput Graph::sssp(UIN src, SSSPConfig config) {
    if (!has_negative_edge_) {
        return sssp_dijkstra(src, config);
    } else {
        // Temporary. Will return Bellman Ford SSSP in the future.
        return SSSPOutput(size());
    }
}

Graph::SSSPOutput Graph::sssp_dijkstra(UIN               src,
                                       const SSSPConfig& config) const {
    Graph::SSSPOutput out(size());

    // { distance_to_src, vertex_id }
    // Sorts ascendingly by the first element: the element that is closest
    // to the source should be at the front of the queue.
    using QueueEntry = pair<LL, UIN>;
    using MinQueue   = set<QueueEntry>;

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

            if (alt < out.dist[v]) {
                // if `src -> ... -> u -> v` is indeed shorter,
                // update `v`'s entry in the queue so that its distance to
                // src reflects the new, shortest distance.

                minqueue.erase(make_pair(out.dist[v], v));
                out.dist[v] = alt;
                out.pred[v] = u;
                minqueue.emplace(out.dist[v], v);
            }
        }
    }

    return out;
}

};  // namespace ds