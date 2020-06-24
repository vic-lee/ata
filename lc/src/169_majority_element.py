"""
169. Majority Element
src: https://leetcode.com/problems/majority-element/
"""

import collections


class Solution:
    """Boyer-Moore Voting Algorithm

    Very interesting. O(1) in memory. See the `solutions` page on Leetcode for
    detailed explanation.

    Useful resources for understanding the algorithm:
    - https://www.youtube.com/watch?v=4Xyhb72LCX4
    - https://www.youtube.com/watch?v=Wj606N0IAsw
    """
    def majorityElement(self, nums):
        count = 0
        candidate = None

        for num in nums:
            if count == 0:
                candidate = num
            count += (1 if num == candidate else -1)

        return candidate


class Solution_2:
    """Pythonic version of solution_v1"""

    def majorityElement(self, nums):
        counts = collections.Counter(nums)
        return max(counts.keys(), key=counts.get)


class Solution_v1:
    def majorityElement(self, nums: List[int]) -> int:
        threshold = len(nums) / 2
        count = {}
        for n in nums:
            if n not in count:
                count[n] = 1
            else:
                count[n] += 1
            if count[n] > threshold:
                return n
