"""
src: https://leetcode.com/problems/two-sum/
"""

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        nums_dict = {}
        for num_idx, num in enumerate(nums):
            counterpart = target - num
            if counterpart not in nums_dict:
                nums_dict[num] = num_idx
            else:
                counterpart_idx = nums_dict[counterpart]
                return [num_idx, counterpart_idx]
