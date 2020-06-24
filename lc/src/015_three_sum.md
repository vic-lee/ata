# Three Num Sum

## Problem description

Given a list of numbers, find 3 numbers from the list such that their sum is 0.

The return value is all the possible combinations. Each number in a given solution must have a unique index (in the list); the values of these numbers, however need not be unique (i.e. `-1, -1, 2` is a valid solution so long as the list of numbers contain two `-1`s).

## Notes

### v1

		`a + b + c = 0	  <==> 	   a + b = -c`

Therefore, in `O(n^2)` we can find all combinations of `a` and `b`s such that 
they sum up to a `-c` (we'd also need to find store a new copy of `nums`, where every number is inversed).

However, this doesn't solve the issue of duplicate solutions. A unique solution
can be defined by a set of 3 numbers, wherein their indices are unique, and 
their values sum up to 0. 

Since a number is identified by both its index (which helps us prevent 
replicating solutions) and its value (which helps us find zero-sums), we can 
implement a key-value mapping of the `nums` list in which the key is a number's index and the value its value. Our solution, prior to returning, should be a 
list of unique index-based sets. The sets are to be guaranteed to have zero-sum.

We use a double-for loop to identify all the `a + b` pairs. Once we find a pair such that their sum equals `-c`, where c is a number in a list, we have a candidate. We then create an index-based set. After this, we check if this set is already in our answer list; if not, we have a valid answer.

At return, we use the hash table to convert the index-based sets to val-based 
lists. The actual return value is a 2-D array.

### v2

An unique solution is not defined by a unique index-based set, because numbers
at different indices may have the same value, therefore leading to duplicate
solutions. 

Therefore, a solution should be defined by a key-val pair where the key is a
number's value and the value is how many times they occur. For instance, 
`(1, 1, -2)` is represented as `{"1": 2, "-2": 1}`.
