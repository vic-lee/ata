# Graph test cases

## Universal graph input format (UGIF)

Graph test cases should conform to the UGIF format, as described below. Use
`graph_reader` to perform input parsing.

```
<num_vertices> <num_edges> <D | UD> <W | UW>
u v [w]
u v [w]
...
u v [w]
```

The first line denotes necessary configurations for the Graph instance.

- `num_vertices` is an integer where `0 <= num_vertices <= INT_MAX`
- `num_edges` is an integer where `0 <= num_edges <= INT_MAX`
- The third entry configures whether the graph is directed or not. It has two
    possible input values: `D` for directed, and `UD` for undirected.
- The fourth entry configures whether the graph is weighted or not. It has
    two possible input values: `W` for weighted, and `UW` for unweighted.

The input then contains `num_edges` lines, each corresponding to an edge.
Each line may contain 2 or 3 numbers, depending on whether the graph is 
weigthed:

- `u`: where the edge originates from. `0 <= u < V`.
- `v`: where the edge goes to. `0 <= v < V`.
- `w`: the weight of the edge. Provided only if the graph is set to weighted.
    `INT_MIN <= w <= INT_MAX`.

Certain test suites may contain tests in legacy formats, in which case the
format used is described in their driver file's `read_in()` method.
