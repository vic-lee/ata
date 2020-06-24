# Dynamic programming (DP)

## DP = recursion + memoization + guessing

- Memoize & re-use solutions (to sub-problems)
- `time = #subproblems * (time/sub-prob)`
  - recursions don't count because if a subproblem is calculated, it is memoized

## Bottom-up DP algorithms

- exactly same computation as the memoized solution. 
- Think of it as a topological sort of dependency DAGs (directed acyclic graph)
  - *Elaboration*: for instance, to find Fib(n) we are dependent on Fib(n-1) and Fib(n-2). Therefore, a bottom-up approach finds Fib(n-1) and Fib(n-2) first, then the solution to Fib(n) is readily apparent. 
  - **Note**: subproblem dependencies should be *acyclic*

Don't know the answer? Guess. Specifically, guess *all* the possible answers.

After all guesses are exhausted, we pick *the best one* (optimization). 