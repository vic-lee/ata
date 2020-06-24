"""
509. Fibonacci Number
src: https://leetcode.com/problems/fibonacci-number/
"""


class Solution:
    """
    Result
    ------
    - Runtime:      28ms    (98.04%)
    - Memory:       13.1Mb  (77.15%)

    Key takeaways
    -------------
    - Identify whether recursive calls are repetitive calculations
        -> use `memoization` if repetitive
    """

    def __init__(self):
        self.memo = {}

    def fib(self, n: int) -> int:
        if n == 0:
            return 0
        elif n == 1:
            return 1
        else:
            if n - 1 not in self.memo:
                self.memo[n-1] = self.fib(n-1)
            if n - 2 not in self.memo:
                self.memo[n-2] = self.fib(n-2)
            return self.memo[n-1] + self.memo[n-2]


class Solution_alt:
    """
    A bottom-up, non-recursive, memoized solution. Computationally, this
    solution is identical to the one above.

    Result
    ------
    - Runtime:      32ms    (91.93%)
    - Memory:       13Mb    (91.37%)
    """

    def __init__(self):
        self.memo = {}

    def fib(self, n: int) -> int:
        for n in range(n+1):
            if n == 0:
                self.memo[n] = 0
            elif n == 1:
                self.memo[n] = 1
            else:
                self.memo[n] = self.memo[n-1] + self.memo[n-2]
        return self.memo[n]
