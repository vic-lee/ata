"""
543. Diameter of Binary Tree
src: https://leetcode.com/problems/diameter-of-binary-tree/
"""


class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        self.sol = 0
        
        def depth(node):
            if not node:
                return 0
            L, R = depth(node.left), depth(node.right)
            self.sol = max(self.sol, L+R)
            print(self.sol, node.val, L, R)
            return max(L, R) + 1
        
        depth(root)
        return self.sol