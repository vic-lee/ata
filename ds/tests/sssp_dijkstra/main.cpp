#include <iostream>
#include <sstream>
#include <vector>

#include "graph.hpp"

#define FOR_N(n) for (size_t i = 0; i < n; i++)

using UIN = unsigned int;
using ULL = unsigned long long;

struct ProcessedInput {
    ds::Graph g;
    size_t    src_vertex;
};

/**
 * Dijkstra input format:
 *
 * V: number of vertices
 * E: number of edges
 * S: the source vertex from which Dijkstra begins
 *
 * followed by `E` lines of `u v w`s where u v are the vertex IDs, and w the
 * weight of the edge.
 *
 * Constraints:
 *
 * - 0 <= V <= INT_MAX
 * - 0 <= E <= INT_MAX
 * - 0 <= S <= V
 * - for each u, v pair, 0 <= u, v <= V
 * - INT_MIN <= w <= INT_MAX
 *
 * @example
 * ```
 * V E S
 * u v w
 * u v w
 * ...
 * u v w
 * ```
 */
ProcessedInput read_in() {
    UIN num_vertices, num_edges, src_vertex;
    cin >> num_vertices >> num_edges >> src_vertex;

    ds::Graph g(num_vertices);

    UIN u, v;
    LL  w;
    FOR_N(num_edges) {
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    return {g, src_vertex};
}

void fmtout(const ds::Graph::SSSPOutput& out) {
    FOR_N(out.dist.size()) {
        auto dist = out.dist[i];

        if (dist == ds::Graph::DIST_INFTY) {
            cout << "INF";
        } else {
            cout << dist;
        }

        if (i != out.dist.size() - 1) {
            cout << " ";
        }
    }

    cout << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    auto [g, src_vertex] = read_in();
    auto out             = g.sssp(src_vertex);
    fmtout(out);
}
