"""
637. Average of Levels in Binary Tree
src: https://leetcode.com/problems/average-of-levels-in-binary-tree/
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    """
    Result
    ------
    - Runtime:      56ms    (91.26%)
    - Memory:       15.4Mb  (90.65%)

    Improvements
    ------------
    - Simplified `mean()`
    """
    def averageOfLevels(self, root: TreeNode) -> List[float]:
        if not root:
            return []

        level = [root]
        ans = []
        while len(level) > 0:
            ans.append(self.mean(level))
            next_level = []
            for node in level:
                if node.left:
                    next_level.append(node.left)
                if node.right:
                    next_level.append(node.right)
            level = next_level

        return ans

    def mean(self, lst: List[TreeNode]) -> float:
        return sum(map(lambda n: n.val, lst)) / len(lst)


class Solution_v1:
    def averageOfLevels(self, root: TreeNode) -> List[float]:
        if not root:
            return []

        level = [root]
        ans = []
        while len(level) > 0:

            next_level = []
            for node in level:
                if node.left:
                    next_level.append(node.left)
                if node.right:
                    next_level.append(node.right)

            ans.append(self.mean(level))
            level = next_level

        return ans

    def mean(self, lst: List[TreeNode]) -> float:
        sum = 0
        for node in lst:
            sum += node.val
        return sum / len(lst)
