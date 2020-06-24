"""
70:     Climing Stairs
src:    https://leetcode.com/problems/climbing-stairs/
"""


class Solution_v2_iterative:
    """
    Iterative solution (that is equivalent to the recursive one below),
    for better memory performance.
    """
    def __init__(self):
        self.memo = {1: 1, 2: 2}

    def climbStairs(self, n: int) -> int:
        if n in self.memo:
            return self.memo[n]
        for i in range(3, n+1):
            self.memo[i] = self.memo[i-2] + self.memo[i-1]
        return self.memo[n]


class Solution_v2_recursive:
    """
    The key insight here is that solution N(n) = N(n-1) + N(n-2)
    """
    def __init__(self):
        self.memo = {1: 1, 2: 2}

    def climbStairs(self, n: int) -> int:
        if n in self.memo:
            return self.memo[n]
        self.memo[n] = self.climbStairs(n-2) + self.climbStairs(n-1)
        return self.memo[n]


class Solution_v1:
    """
    Attempt 1. Time complexity: 2^n. 
    """

    def climbStairs(self, n: int) -> int:
        if n == 1:
            return 1
        return self.climb_recursive(0, n)

    def climb_recursive(self, sum: int, target: int):
        if sum > target:
            return 0
        if sum == target:
            return 1
        return self.climb_recursive(sum+1, target) \
            + self.climb_recursive(sum+2, target)
