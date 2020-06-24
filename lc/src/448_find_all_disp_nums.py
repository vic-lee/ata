"""
448. Find All Numbers Disappeared in an Array
src: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
"""


class Solution_v3:
    """An optimized v1.

    We don't need to convert nums to a set. Runtime reduced from 400ms to 
    384ms, now faster than 93.9%.
    """
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        possibles = list(range(1, len(nums)+1))
        for n in nums:
            possibles[n-1] = -1
        return [p for p in possibles if p != -1]


class Solution_v2:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        return list(set(range(1, len(nums)+1)) - set(nums))


class Solution_v1:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        possibles = list(range(1, len(nums)+1))
        actuals = set(nums)

        for a in actuals:
            possibles[a-1] = -1

        return [p for p in possibles if p != -1]
