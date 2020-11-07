# Graph

This is a custom implementation of a graph and its typical functionalities, in
C++.

## Goal

The goal of this graph implementation is to abstract away the different
implementation details when a graph is weighted / unweighted, or when it is
directed / undirected. For instance, rather than thinking about which
algorithm to use to find a graph's all-pairs shortest paths (APSP) output,
a convenient `apsp()` method is provided.

## Graph initialization and configuration

Use `GraphConfig` to configure the weightedness and directionality of a graph
instance.

```cpp
// for instance, to instantiate a directed, unweighted graph:

unsigned int num_vertices = 100;

bool is_directed = true;
bool is_weighted = false;

auto config = ds::Graph::GraphConfig(is_directed, is_weighted);

auto g = ds::Graph(num_vertices, config);
```

## Functionalities

Below are a list of frequently invoked functionalities. For a list of all the
functionalities implemented, see `graph.hpp`.

| Method | Description |
| --- | --- |
| `has_negative_cycle` | Determines whether a graph contains any negative cycle(s). |
| `is_bipartite` | Determines whether a graph's vertices can be partitioned into two sets such that every edge goes from one set to the other. |
| `is_a_tree` | Determines whether a graph is acyclic and undireced. |
| `is_connected` | Determines whether there exists a path from every vertex to every other vertices in a graph. |
| `find_all_reachables` | From a vertex, find all vertices that are reacheable from the provided vertex. |
| `sssp` | Given a source vertex, compute the shortest paths to all the other vertices. |
|`apsp` | Compute the shortest paths for every vertex pair. |

The implementation is based on adjacency lists, although a utility method is
provided to convert to an equivalent adjacency matrix representation.

## Tests

Each addition to the graph's functionality comes with additions to the test
suite. For more detail about how graph test cases are formatted and organized,
see the `tests` folder in this folder.
