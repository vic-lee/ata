#include "graph.hpp"

#include <unordered_set>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;

namespace ds {

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

void Graph::find_all_reachables(UIN src, vector<bool>& visited) const {
    visited[src] = true;
    for (auto const& next_candidate : adj_[src]) {
        if (!visited[next_candidate]) {
            find_all_reachables(next_candidate, visited);
        }
    }
}

};