#include <iostream>

#include "graph.hpp"
#include "tests/graph_reader.hpp"

int main(int argc, const char* argv[]) {
    auto g = read_graph_input();
    std::cout << (g.is_bipartite() ? "YES" : "NO") << std::endl;
}