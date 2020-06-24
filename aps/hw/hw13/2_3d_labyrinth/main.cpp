#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;
using UIN = unsigned int;
using LL  = long long;
using ULL = unsigned long long;

const int NO_PATH = 270100;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << ' ';
    }
    cout << oss.str() << endl;
}

class Graph {
    struct Edge {
        UIN u;
        UIN v;
        LL  weight;
    };

    vector<UIN>                nodes_;
    vector<unordered_set<UIN>> adj_;
    vector<Edge>               edges_;

   public:
    Graph(UIN size) {
        nodes_ = vector<UIN>(size, 0);
        adj_   = vector<unordered_set<UIN>>(size);
    }

    void add_edge(UIN u, UIN v, LL w = 0) {
        adj_[u].insert(v);
        adj_[v].insert(u);
        edges_.push_back({u, v, w});
    }

    bool shortest_path_unweighted(UIN dest, UIN src, vector<LL>& dist) {
        auto visited = vector<bool>(size(), false);

        visited[src] = true;
        dist[src]    = 0;
        queue<UIN> queue;
        queue.push(src);

        while (!queue.empty()) {
            UIN u = queue.front();
            queue.pop();

            for (auto const v : adj_[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    dist[v]    = dist[u] + 1;
                    queue.push(v);

                    if (v == dest) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Returns true if the graph has negative cycle(s), false otherwise.
    // The function is idempotent.
    bool has_negative_cycle() const {
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

    // Returns the number of nodes within this graph.
    size_t size() const { return nodes_.size(); }
};

struct Coor {
    int x;
    int y;
    int z;
};

bool operator==(const Coor& self, const Coor& other) {
    return self.x == other.x && self.y == other.y && self.z == other.z;
}

using Maze = vector<vector<vector<char>>>;

struct Input {
    Maze maze;
    Coor start;
    Coor end;
};

Input read_in() {
    UIN K, N, M;
    cin >> K >> N >> M;
    Input in;

    in.maze = vector<vector<vector<char>>>(
        K, vector<vector<char>>(N, vector<char>(M, ' ')));

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> in.maze[i][j][k];

                if (in.maze[i][j][k] == 'S') {
                    in.start = {i, j, k};
                } else if (in.maze[i][j][k] == 'E') {
                    in.end = {i, j, k};
                }
            }
        }
    }

    return in;
}

using EscapeTimes = vector<vector<vector<int>>>;
using VisitMap    = vector<vector<vector<bool>>>;

int plan_escape(Input& in) {
    UIN   K = in.maze.size(), M = in.maze[0].size(), N = in.maze[0][0].size();
    auto  graph_sz = K * M * N;
    Graph g(graph_sz);

    auto to_node_id = [K, M, N](Coor coor) {
        return N * M * coor.x + N * coor.y + coor.z;
    };

    auto is_rock = [&in](int i, int j, int k) {
        return in.maze[i][j][k] == '#';
    };

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                if (is_rock(i, j, k)) {
                    continue;
                }

                auto self_id = to_node_id({i, j, k});
                if (k > 0 && !is_rock(i, j, k - 1)) {
                    g.add_edge(self_id, to_node_id({i, j, k - 1}), 1);
                }
                if (k < (N - 1) && !is_rock(i, j, k + 1)) {
                    g.add_edge(self_id, to_node_id({i, j, k + 1}), 1);
                }

                if (j > 0 && !is_rock(i, j - 1, k)) {
                    g.add_edge(self_id, to_node_id({i, j - 1, k}), 1);
                }

                if (j < (M - 1) && !is_rock(i, j + 1, k)) {
                    g.add_edge(self_id, to_node_id({i, j + 1, k}), 1);
                }

                if (i > 0 && !is_rock(i - 1, j, k)) {
                    g.add_edge(self_id, to_node_id({i - 1, j, k}), 1);
                }

                if (i < (K - 1) && !is_rock(i + 1, j, k)) {
                    g.add_edge(self_id, to_node_id({i + 1, j, k}), 1);
                }
            }
        }
    }

    vector<LL> dist = vector<LL>(graph_sz, LLONG_MAX);

    bool reachable = g.shortest_path_unweighted(to_node_id(in.end),
                                                to_node_id(in.start), dist);

    if (!reachable) {
        cout << "Trapped!" << endl;
    } else {
        cout << "Escaped in " << dist[to_node_id(in.end)] << " minute(s)."
             << endl;
    }

    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in  = read_in();
    auto out = plan_escape(in);
}
