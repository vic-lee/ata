#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

/**********************************************************
 * V4
 * A more conventional approach that uses DFS.
 **********************************************************/

class Solution
{
public:
    enum VisitStatus
    {
        not_visited,
        visited,    /* node visited, but if encountered by its children ==> cycle */
        safe
    };

    bool DFS(int src, vector<vector<int>> &graph, vector<VisitStatus> &visit_history)
    {
        visit_history[src] = visited;

        for (int i = 0; i < graph[src].size(); i++)
        {
            if (visit_history[graph[src][i]] == not_visited)
            {
                if (DFS(graph[src][i], graph, visit_history))
                {
                    return true;
                }
            }
            else if (visit_history[graph[src][i]] == visited) /* cycle: encountered by children */
            {
                return true;
            }
        }
        visit_history[src] = safe;
        return false;
    }

    bool canFinish(int num_courses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> graph(num_courses, vector<int>{});

        int sz = prerequisites.size();
        vector<VisitStatus> visit_history(num_courses, not_visited);

        for (int i = 0; i < sz; i++)
        {
            graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        bool flag = false;

        for (int i = 0; i < num_courses; i++)
        {
            if (flag)
            {
                break;
            }
            if (visit_history[i] == 0)
            {
                flag = DFS(i, graph, visit_history);
            }
        }
        return !flag;
    }
};

/**********************************************************
 * V3
 * Assume course_nums < n, which is a valid assumption (oth-
 * erwise we can't use course_num for vector indices).
 * 
 **********************************************************/

class Solution
{
public:
    bool canFinish(int n, vector<vector<int>> &pre)
    {
        vector<vector<int>> adj(n, vector<int>());
        vector<int> degree(n, 0);
        for (auto &p : pre)
        {
            adj[p[1]].push_back(p[0]);
            degree[p[0]]++;
        }
        cout << "degrees" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "degree of " << i << " is " << degree[i] << endl;
        }
        cout << "adjacencies" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i << "'s adjacent vertices are: ";
            for (int j = 0; j < adj[i].size(); j++)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
        queue<int> q; /* queue only contains isolated vertices */
        cout << "queueing" << endl;
        for (int i = 0; i < n; i++)
        {
            if (degree[i] == 0)
            {
                q.push(i);
                cout << i << endl;
            }
        }
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            n--;
            for (auto next : adj[curr])
            {
                if (--degree[next] == 0) /* if the only neighbor of this node is self */
                {
                    q.push(next);
                }
            }
        }
        return n == 0;
    }
};

/**********************************************************
 * V2
 * Ideally, we don't need to create a graph before analyzing,
 * as this would require the runtime to be at least 2V. 
 **********************************************************/

/**
 * Graph_: {
 *  vertex: {
 *    visited: true/false, 
 *    adjacencies: []
 *  }
 * }
 * NTS: adjacency list is not going to work for directional graphs;
 * for directional graphs, it is not sufficient to maintain a `visited` list;
 * we need to keep track of ancestry relationships.
 */

class Graph
{
public:
    Graph(vector<vector<int>> &edges);
    int size();
    bool acyclic_dfs();
    void add_edge(int vertex, int adj);

private:
    bool perform_acyclic_dfs(int vertex);
    map<int, pair<bool, vector<int>>> graph_;
};

Graph::Graph(vector<vector<int>> &edges)
{
    for (auto edge : edges)
    {
        add_edge(edge[0], edge[1]);
    }
}

void Graph::add_edge(int vertex, int adj)
{
    graph_[vertex].second.push_back(adj);
}

bool Graph::acyclic_dfs()
{
    for (auto it = graph_.begin(); it != graph_.end(); it++)
    {
        if (!it->second.first)
        {
            bool cyclical = perform_acyclic_dfs(it->first);
            if (cyclical)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Graph::perform_acyclic_dfs(int vertex)
{
    graph_[vertex].first = true;
    for (int adj : graph_[vertex].second)
    {
        if (!graph_[adj].first)
        {
            bool cyclical = perform_acyclic_dfs(adj);
            if (cyclical)
            {
                return false;
            }
        }
    }
    return true;
}

int Graph::size()
{
    return graph_.size();
}

class Solution_v2
{
public:
    /**
     * Prerequisites are edges; not nodes.
     */
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        Graph g(prerequisites);
        if (g.acyclic_dfs()) /* no cycle */
        {
            cout << "Acyclic; gsize: " << g.size() << "; numcourses: " << numCourses << endl;
            return numCourses >= g.size();
        }
        else
        {
            cout << "cyclic" << endl;
            return false;
        }
    }
};

/**********************************************************
 * V1
 * Naive solution.
 * ParentsMap is expensive to maintain.
 **********************************************************/

class Solution_v1
{
public:
    typedef map<int, vector<int>> ParentsMap;
    typedef map<int, vector<int>> Graph;

    /* O(V) runtime */
    map<int, vector<int>> load_graph(const vector<vector<int>> &prerequisites)
    {
        map<int, vector<int>> graph;
        for (auto const &requirement : prerequisites)
        {
            int self = requirement[0];
            int dependency = requirement[1];
            graph[self].push_back(dependency);
        }
        return graph;
    }

    bool visit(Graph &graph, ParentsMap &parents, int vertex)
    {
        for (auto &dependency : graph[vertex])
        {
            if (find(parents[vertex].begin(), parents[vertex].end(), dependency) != parents[vertex].end())
            {
                return true;
            }
            auto it = parents.find(dependency);
            if (it == parents.end())
            {
                vector<int> new_parent_list = parents[vertex];
                new_parent_list.push_back(vertex);
                parents[dependency] = new_parent_list;

                bool found_cycle = visit(graph, parents, dependency);

                if (found_cycle)
                    return true;
                else
                    continue;
            }
        }
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        ParentsMap parents;
        Graph graph = load_graph(prerequisites);

        for (auto &vertex : graph)
        {
            if (parents.find(vertex.first) == parents.end())
            {
                parents[vertex.first];
                bool found_cycle = visit(graph, parents, vertex.first);
                if (found_cycle == true)
                {
                    return false;
                }
            }
        }

        if (graph.size() > numCourses)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};