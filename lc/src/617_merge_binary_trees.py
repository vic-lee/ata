"""
617. Merge Two Binary Trees
src: https://leetcode.com/problems/merge-two-binary-trees/
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def mergeTrees(self, t1: TreeNode, t2: TreeNode) -> TreeNode:
        """Keep merging until one node ends. Then copy the rest of the tree"""

        # Return None if there's nothing to merge
        if not t1 and not t2:
            return None

        if t1 and t2:
            # if both nodes are non-empty, the current root node would have
            # the sum of the two as its value. Then, recursively get the values
            # for the left side and the right side of the node. 
            merged = TreeNode(t1.val + t2.val)                    
            merged.left = self.mergeTrees(t1.left, t2.left)
            merged.right = self.mergeTrees(t1.right, t2.right)
            return merged
            
        # else if any of the nodes are None, simply return the other node
        elif t1:
            return t1
        elif t2:
            return t2

