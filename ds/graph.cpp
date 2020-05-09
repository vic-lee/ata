#include <vector>

using namespace std;
using UIN = unsigned int;

class Graph {
    vector<UIN>         nodes_;
    vector<vector<UIN>> adj_;

   public:
    Graph(UIN size) {
        nodes_ = vector<UIN>(size, 0);
        adj_   = vector<vector<UIN>>(size);
    }

    void add_edge(UIN u, UIN v) {
        adj_[u].push_back(v);
        adj_[v].push_back(u);
    }

    /** Mark all nodes reachable from `src` as visited */
    void dfs(UIN src, vector<bool>& visited) {
        visited[src] = true;
        for (size_t i = 0; i < adj_[src].size(); i++) {
            UIN next_candidate = adj_[src][i];
            if (!visited[next_candidate]) {
                dfs(next_candidate, visited);
            }
        }
    }
};
