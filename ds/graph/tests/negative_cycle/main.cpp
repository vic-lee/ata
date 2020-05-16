#include <iostream>
#include <sstream>
#include <vector>

#include "graph.hpp"

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using UIN = unsigned int;
using ULL = unsigned long long;

ds::Graph read_in() {
    UIN num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;

    ds::Graph::GraphConfig config = {
        true,  // directed graph
        true,  // weighted graph
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

int main() {
    auto g = read_in();
    std::cout << (g.has_negative_cycle() ? "YES" : "NO") << std::endl;
}
