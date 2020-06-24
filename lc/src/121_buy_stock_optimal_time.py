"""
121. Best Time to Buy and Sell Stock
"""


class Solution:
    """
    O(n) time, O(1) space.
    """
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) == 0:
            return 0
        
        cur = prices[0]
        max_profit = 0
        
        for i in range(len(prices)):
            cur = min(cur, prices[i])
            max_profit = max(max_profit, prices[i]-cur)
        
        return max(max_profit, 0)