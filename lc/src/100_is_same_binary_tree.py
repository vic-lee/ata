"""
100. Same Tree
src: https://leetcode.com/problems/same-tree/submissions/
"""


class Solution:
    """
    Improvements
    ------------
    This is a sample 20ms solution. While I couldn't reproduce the same results, 
    the algorithm is very simple and its correctness is readily apparent. 
    
    Compared with my solution, this solution costs much less memory as it does
    not involve array-building.

    Key takeaways
    -------------
    - Prefer simple boolean determinants to buliding complex DSs
    """
    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:
        if p is None and q is None:
            return True
        elif p is None or q is None:
            return False
        elif p.val != q.val:
            return False

        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)


class Solution_v1:
    """
    Results
    -------
    Runtime:        32ms    (92.12%)
    Memory:         13.2Mb  (47%)

    Repeated list concatination can hit performance.
    """
    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:
        return self.tree_to_arr(p) == self.tree_to_arr(q)

    def tree_to_arr(self, n: TreeNode) -> List[int]:
        sol = []

        if n is None:
            return [None]

        sol += [n.val]

        if n.left and n.right:
            sol += [n.left.val, n.right.val]
            sol += self.tree_to_arr(n.left)
            sol += self.tree_to_arr(n.right)

        elif n.left:
            sol += [n.left.val, None]
            sol += self.tree_to_arr(n.left)

        elif n.right:
            sol += [None, n.right.val]
            sol += self.tree_to_arr(n.right)

        else:
            sol += [None, None]

        return sol
