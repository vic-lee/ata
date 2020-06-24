"""
Combination Sum 
src: https://leetcode.com/problems/combination-sum/
"""

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        i_max = bisect.bisect_right(candidates, target)
        candidates = candidates[:i_max]
        return self.findcomb(candidates, parent=target, remaining_sum=target)

    def findcomb(self, candidates: List[int], parent: int, remaining_sum: int):
        """
        Input:      a list of candidates, a sum to find.
        Output:     all possibble solutions that candidates add up to the sum.
        """
        max_considered = bisect.bisect_right(candidates,
                                             min(parent, remaining_sum))
        if len(candidates[:max_considered]) == 0:
            return []
        elif len(candidates[:max_considered]) == 1:
            the_candidate = candidates[0]
            if remaining_sum % the_candidate == 0:
                return [[the_candidate] * (remaining_sum // the_candidate)]
            else:
                return []
        else:
            ans = []
            for candidate in candidates[:max_considered]:
                next_remaining_sum = remaining_sum - candidate
                if next_remaining_sum == 0:
                    ans.append([candidate])
                else:
                    paths = self.findcomb(candidates,
                                          parent=candidate,
                                          remaining_sum=next_remaining_sum)
                    self.append_paths(candidate, paths, ans)
            return ans

    def append_paths(self, parent, paths, ans):
        """
        Add the new paths to the answers, by first appending the parent node to the paths. 
        """
        if paths != []:
            paths = [path + [parent] for path in paths]
            ans += paths
