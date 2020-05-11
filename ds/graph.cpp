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
    Graph::SSSPOutput out(size());

    // { vertex_id, distance_to_src }
    using QueueEntry = pair<UIN, LL>;

    if (!has_negative_edge_) {
        using MinQueue = set<QueueEntry>;

        MinQueue minqueue;

        out.dist[src] = 0;
        minqueue.emplace(src, out.dist[src]);

        while (!minqueue.empty()) {
            auto min_dist_entry = *minqueue.begin();
            minqueue.erase(minqueue.begin());
            auto u = min_dist_entry.first;

            for (auto const& edge : adj_[u]) {
                auto v   = edge.id;
                LL   alt = out.dist[u] + edge.edge_weight;

                if (alt < out.dist[v]) {
                    minqueue.erase(make_pair(v, out.dist[v]));
                    out.dist[v] = alt;
                    out.pred[v] = u;
                    minqueue.emplace(v, out.dist[v]);
                }
            }
        }
    }

    return out;
}

};  // namespace ds