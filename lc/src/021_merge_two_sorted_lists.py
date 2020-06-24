"""
21. Merge Two Sorted Lists
src: https://leetcode.com/problems/merge-two-sorted-lists/
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution:
    """
    Improvements
    ------------

    - no need to instantiate new ListNodes when creating the sorted merged list; 
        simply use nodes constructed in L1 and L2

    - no need to copy over the remaining list to the sorted list; 
        this is a linked-list question, and ll-nodes are merely references

    - the algorithm is resistant to l1 and l2 being None;
        we don't need to perform error checks before algorithm

    Key Takeaways
    -------------
    
    1. Avoid copying operations in LL-related questions; they're often unnessary
    2. When possible, prefer using original list nodes to constructing new nodes
    """
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        
        sorted_head = ListNode(None)
        cur = sorted_head
        
        while l1 and l2:
            if l1.val < l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next
            cur = cur.next

        if l1:
            cur.next = l1
        
        elif l2:
            cur.next = l2
            
        return sorted_head.next


class Solution_v1:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:

        if l1 is None and l2 is None:
            return []
        elif l1 is None:
            return l2
        elif l2 is None:
            return l1

        if l1.val < l2.val:
            sorted_list = ListNode(l1.val)
            l1 = l1.next
        else:
            sorted_list = ListNode(l2.val)
            l2 = l2.next

        cur = sorted_list

        while l1 is not None and l2 is not None:
            if l1.val < l2.val:
                cur, l1 = self.append_and_increment(cur, l1)
            else:
                cur, l2 = self.append_and_increment(cur, l2)

        if l1 is not None:
            cur = self.append_the_remaining_list(cur, l1)

        if l2 is not None:
            cur = self.append_the_remaining_list(cur, l2)

        return sorted_list

    def append_and_increment(self, cur: ListNode,
                             lst: ListNode) -> (ListNode, ListNode):
        cur.next = ListNode(lst.val)
        cur = cur.next
        lst = lst.next
        return cur, lst

    def append_the_remaining_list(self, cur: ListNode,
                                  lst: ListNode) -> ListNode:
        while lst is not None:
            cur.next = ListNode(lst.val)
            cur = cur.next
            lst = lst.next
        return cur
