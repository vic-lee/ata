"""
226. Invert Binary Tree
src: https://leetcode.com/problems/invert-binary-tree/
"""


class Solution:
    """Logically equivalent to the second solution, but simplified.

    I find the second solution more readable; you may disagree.

    One important note is
    >>> root.left, root.right = self.invertTree(root.right), self.invertTree(root.left)
    is not equivalent to 
    >>> root.left = self.invertTree(root.right)
    >>> root.right = self.invertTree(root.left)

    Note that in the line 2 of the second implementation, `root.left` has been
    overwritten in line 1 to the inverted `root.right`. Understandably, this 
    would not lead to the correct results -- it would probably lead to many 
    duplicate nodes.
    """

    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root:
            return None
        root.left, root.right = self.invertTree(root.right), self.invertTree(root.left)
        return root


class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root:
            return None
        root.left, root.right = root.right, root.left
        root.left = self.invertTree(root.right)
        root.right = self.invertTree(root.left)
        return root
