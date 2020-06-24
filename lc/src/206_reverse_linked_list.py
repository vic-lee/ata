class Solution_recursive:
    def reverseList(self, head: ListNode) -> ListNode:
        return self._reverse(head)
    
    def _reverse(self, cur: ListNode, prev=None) -> ListNode:
        if not cur:
            return prev
        next_cur = cur.next
        cur.next = prev
        return self._reverse(next_cur, cur)

