#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

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

struct Input {
    UIN                 num_emps;
    UIN                 num_langs;
    vector<vector<UIN>> lang_to_emp;
};

Input read_in() {
    Input in;

    UIN num_langs_for_employee;
    cin >> in.num_emps >> in.num_langs;
    in.lang_to_emp = vector<vector<UIN>>(in.num_langs + 1);

    for (size_t emp_id = 0; emp_id < in.num_emps; emp_id++) {
        cin >> num_langs_for_employee;
        UIN lang_id;
        for (size_t j = 0; j < num_langs_for_employee; j++) {
            cin >> lang_id;
            in.lang_to_emp[lang_id].push_back(emp_id);
        }
    }

    return in;
}

void process(Input& in) {
    Graph g = Graph(in.num_emps);
    // connect all employees who can already communicate
    for (size_t lang_id = 1; lang_id < in.lang_to_emp.size(); lang_id++) {
        if (in.lang_to_emp[lang_id].size() >= 2) {
            for (size_t j = 0; j < in.lang_to_emp[lang_id].size() - 1; j++) {
                // no need to add all bilateral edges among all employees who
                // speak this language. only need to ensure they are all
                // connected.
                UIN cur  = in.lang_to_emp[lang_id][j],
                    next = in.lang_to_emp[lang_id][j + 1];
                g.add_edge(cur, next);
            }
        }
    }

    // count number of components in this graph
    UIN  component_count = 0;
    auto visited         = vector<bool>(in.num_emps, false);

    for (size_t node_id = 0; node_id < visited.size(); node_id++) {
        if (!visited[node_id]) {
            g.dfs(node_id, visited);
            component_count++;
        }
    }

    // require (component - 1) number of edges to make this a connected graph
    cout << component_count - 1 << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    process(in);
}
