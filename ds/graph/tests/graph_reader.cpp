#include "graph_reader.hpp"

#include <iostream>

#include "graph.hpp"

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using UIN = unsigned int;
using LL  = long long;

ds::Graph read_graph_input() {
    std::string directed_graph_mode, weighted_graph_mode;
    UIN         num_vertices, num_edges;

    std::cin >> num_vertices >> num_edges >> directed_graph_mode >>
        weighted_graph_mode;

    bool is_directed = directed_graph_mode == "D",
         is_weighted = weighted_graph_mode == "W";

    auto config = ds::Graph::GraphConfig(is_directed, is_weighted);

    auto g = ds::Graph(num_vertices, config);

    UIN u, v;
    LL  w;
    FOR_N(num_edges) {
        if (is_weighted) {
            std::cin >> u >> v >> w;
            g.add_edge(u, v, w);
        } else {
            std::cin >> u >> v;
            g.add_edge(u, v);
        }
    }

    return g;
}
