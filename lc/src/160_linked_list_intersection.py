"""
160. Intersection of Two Linked Lists
src: https://leetcode.com/problems/intersection-of-two-linked-lists/
"""

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution(object):
    """
    Result
    ------
    Runtime:    172ms   (99.65%)
    Memory:     41.8Mb  (44.34%)

    Notes
    -----
    This is not an original solution. My original solution is a brute force one,
    with a runtime of O(M*N). A hash-table based solution was considered because
    of its benefits in lookup (it should reduce time complexity to O(M+N)); this 
    was not implemented because of difficulty / workarounds required to hash
    objects in Python. 

    The best so˝lution, listed below, is quite ingenious. Having had 2 LL ptrs
    set up, we set the shorter list ptr to point to the other list's head. After
    2 iterations, because `len(A) + len(B) == len(B) + len(A)`, both ptrs finish
    both ptrs, and the loop ends.

    Consider: 
                  switch
    4->1->8->4->5->5->0->1->8->4->5
    5->0->1->8->4->5->4->1->8->4->5
                     switch HIT

    The loop must end because, if pA != pB for 2 iterations (i.e. there's no
    intersection), at the end of the lists, they simultaneously set them to
    `.next`, which is None. `pA == pB == None` forces the loop to end. 
    """
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB:
            return None

        pA, pB = headA, headB

        while pA is not pB:
            pA = headB if not pA else pA.next
            pB = headA if not pB else pB.next

        return pA
