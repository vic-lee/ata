"""
617: Maximum Binary Tree Depth
src: https://leetcode.com/problems/maximum-depth-of-binary-tree/
"""


class Solution:
    """
    Figured out a way to increment 1 without passing in and out `current_depth`.

    Future recursion problems should follow this format to avoid unnessarily
    passing in parameters (and thereby creating a new func for regression).
    """

    def maxDepth(self, root: TreeNode) -> int:
        if not root:
            return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))


class Solution_v1:
    def maxDepth(self, root: TreeNode) -> int:
        return self.find_max_depth(root, 0)

    def find_max_depth(self, node: TreeNode, current_depth: int) -> int:
        if not node:
            return current_depth
        return max(self.find_max_depth(node.left, current_depth+1),
                   self.find_max_depth(node.right, current_depth+1))
