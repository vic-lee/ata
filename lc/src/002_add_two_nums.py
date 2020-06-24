"""
src: https://leetcode.com/problems/add-two-numbers/
"""

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        
        revsum = ListNode(0)
        
        cur1 = l1
        cur2 = l2
        rev_cur = revsum
        carry = 0
        
        while cur1 or cur2:
            rev_cur, carry = self.calc(cur1, cur2, rev_cur, carry)

            cur1 = cur1.next if cur1 else None
            cur2 = cur2.next if cur2 else None
            rev_cur = self.incr_rev_cur(rev_cur) if cur1 or cur2 else rev_cur

        rev_cur = self.perform_carry(rev_cur, carry)
        
        return revsum
                
    def calc(self, cur1: ListNode, cur2: ListNode, rev_cur: ListNode, carry):

        cur1_val = cur1.val if cur1 is not None else 0
        cur2_val = cur2.val if cur2 is not None else 0

        sumdigits = cur1_val + cur2_val + carry
        if sumdigits >= 10:
            carry = 1
            rev_cur.val = sumdigits - 10
        else:
            carry = 0
            rev_cur.val = sumdigits
        return rev_cur, carry

    def incr_rev_cur(self, rev_cur):
        rev_cur.next = ListNode(0)
        rev_cur = rev_cur.next
        return rev_cur

    def perform_carry(self, rev_cur, carry):
        if carry != 0:
            rev_cur = self.incr_rev_cur(rev_cur)
            rev_cur.val += carry
        return rev_cur