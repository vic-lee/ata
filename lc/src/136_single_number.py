"""
136. Single Number
src: https://leetcode.com/problems/single-number/

This is one of the most interesting problems I've solved on Leetcode.
"""


import functools
import operator


class Solution:
    """Use `reduce` and `xor` operator to find the unique num.

    This is my personal favorate solution. This problem is among the rare
    questions where I think using reduce actually makes sense, instead of
    over-complicating your code. By using the xor operator, the list of numbers
    is "reduced" until the one unique value is the last one remaining.
    """

    def singleNumber(self, nums: List[int]) -> int:
        return functools.reduce(operator.xor, nums)


class Solution_reduce:
    """Use `xor` operator, instead of the imported version.

    Second favorite. This is a perfect example of how lambda can be extremely 
    useful.
    """

    def singleNumber(self, nums: List[int]) -> int:
        return functools.reduce(lambda x, y: x ^ y, nums)


class Solution_reduce_simple:
    """Use for loop to iterate through xors.

    Much less elegant compared to the first two solution, although they yield 
    the same result. The benefit of using for loops instead of reduce is how 
    clear and unambiguous it is.
    """
    def singleNumber(self, nums: List[int]) -> int:
        result = 0
        for n in nums:
            result ^= n
        return result


class Solution_sets:
    """Use set difference in sum.

    This is the solution I came up with. While pretty apparent, this solution 
    incurs extra memory overhead, unlike the xor solution.
    """
    def singleNumber(self, nums: List[int]) -> int:
        return 2*sum(set(nums)) - sum(nums)