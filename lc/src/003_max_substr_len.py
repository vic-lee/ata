# src: https://leetcode.com/problems/longest-substring-without-repeating-characters/

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        
        maxlen = 0
        start = 0
        end = 0
        ssmap = {}
        
        while start < n and end < n:
            char = s[end]
            if char in ssmap:
                start = max(ssmap[char], start)
            maxlen = max(maxlen, end - start + 1)
            ssmap[char] = end + 1
            end += 1
        
        return maxlen