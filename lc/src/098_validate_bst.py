# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import math


class Solution:
    """
    Improvements
    ------------
    Use `math.inf` to represent infinity

    Key takeaways
    -------------
    - Think of validating BSTs as refinining upper and lower bounds
    """

    def isValidBST(self, root: TreeNode) -> bool:

        def validate(node: TreeNode, min=-math.inf, max=math.inf):
            if not node:
                return True

            status = node.val > min and node.val < max

            return status if not status else \
                validate(node.left, min=min, max=node.val) \
                and validate(node.right, min=node.val, max=max)

        if not root:
            return True

        return validate(root.left, max=root.val) \
            and validate(root.right, min=root.val)


class Solution_v1:
    def isValidBST(self, root: TreeNode) -> bool:

        def validate(node: TreeNode, min=None, max=None):
            if not node:
                return True

            if min is not None and max is not None:
                status = node.val > min and node.val < max
            elif min is not None:
                status = node.val > min
            elif max is not None:
                status = node.val < max

            return status and validate(node.left, min=min, max=node.val) \
                and validate(node.right, min=node.val, max=max)

        if not root:
            return True

        return validate(root.left, max=root.val) \
            and validate(root.right, min=root.val)
