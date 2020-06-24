"""
155. Min Stack
src: https://leetcode.com/problems/min-stack
"""

class MinStack(object):
    """
    Notes
    -----
    An alternative solution is to keep a 2d list (or a list of 2-elem tuples),
    in which we store 1) the data at the stack, 2) the MIN value associated with
    that stack. This way, we avoid calling `min()` when we need to re-calculate
    in `pop()`.

    `min()` is O(n), so using a 2-d stack should yield better performance. 
    """
    def __init__(self):
        """
        initialize your data structure here.
        """
        self.min = None
        self.data = []
        

    def push(self, x):
        """
        :type x: int
        :rtype: None
        """
        self.data.append(x)
        if self.min is None:
            self.min = x
        elif x < self.min:
            self.min = x

    def pop(self):
        """
        :rtype: None
        """
        removed = self.data[-1]
        del self.data[-1]
        if len(self.data) == 0:
            self.min = None
        elif removed == self.min:
            self.min = min(self.data)
        

    def top(self):
        """
        :rtype: int
        """
        return self.data[-1]
        

    def getMin(self):
        """
        :rtype: int
        """
        return self.min


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()