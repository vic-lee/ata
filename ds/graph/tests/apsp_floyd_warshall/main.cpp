#include <iostream>
#include <sstream>
#include <vector>

#include "graph.hpp"

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using UIN = unsigned int;
using ULL = unsigned long long;

/**
 * APSP input format:
 * ```
 * M V E
 * u v w
 * u v w
 * ...
 * u v w
 * ```
 * where `M` indicates whether a graph is directed or not. Possible values are
 * 'D', which stands for directed graph, and 'U', which stands for undirected.
 */
ds::Graph read_in() {
    char directed;
    UIN  num_vertices, num_edges;
    std::cin >> directed >> num_vertices >> num_edges;

    ds::Graph::GraphConfig config = {
        directed == 'D',  // directed graph
        true,             // weighted graph
    };

    ds::Graph g(num_vertices, config);

    UIN u, v;
    LL  w;
    FOR_N(num_edges) {
        std::cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    return g;
}

void fmtout(const std::vector<std::vector<LL>>& dist) {
    for (size_t i = 0; i < dist.size(); i++) {
        for (size_t j = 0; j < dist[i].size(); j++) {
            if (dist[i][j] == ds::Graph::DIST_INFTY) {
                std::cout << "INF";
            } else {
                std::cout << dist[i][j];
            }

            if (j != dist[i].size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    auto g            = read_in();
    auto [dist, next] = g.apsp();

    fmtout(dist);
}
