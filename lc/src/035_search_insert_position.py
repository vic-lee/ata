"""
The Search Insert Problem
src: https://leetcode.com/problems/search-insert-position/
"""
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        if target > nums[-1]:
            return len(nums)
        elif target <= nums[0]:
            return 0
        for i in range(len(nums) - 1):
            if target >= nums[i] and target <= nums[i+1]:
                return i + 1