"""
My solution to the valide parenthesis problem, in 3 versions. 

src: https://leetcode.com/problems/valid-parentheses/
"""


class Solution:
    """
    Solution v3:
        We further improve the runtime of this algorithm by avoiding the
        `pop()` operation if we are to return False. Note that the `pop`
        statement is executed whether we return True or False in the prior
        implementation; we do not need to pop if we return False.

        A syntax sugar is to check if the stack (i.e. list) is empty
        by `if stack` and `if not stack`.
    """

    def isValid(self, s: str) -> bool:
        close_open_map = {')': '(', '}': '{', ']': '['}
        stack = []
        for i in range(len(s)):
            if s[i] not in close_open_map:
                stack.append(s[i])
            else:
                if stack and stack[-1] == close_open_map[s[i]]:
                    stack.pop()
                else:
                    return False
        return not stack


class Solution_v2:
    """
    Solution v2:
        We replace the close and open char lists with a mapping that is 
        more illustrative of the pairing relationship. 
        With this pairing, we can enable a universal implementation for 
        checking if the close char matches the open char (as opposed to
        the cumbersome switch cases in v1).
    """

    def isValid(self, s: str) -> bool:
        charpairs = {')': '(', '}': '{', ']': '['}
        stack = []
        for i in range(len(s)):
            if s[i] in charpairs.values():
                stack.append(s[i])
            elif s[i] in charpairs:
                if len(stack) == 0:
                    return False
                if stack.pop() != charpairs[s[i]]:
                    return False
        if len(stack) != 0:
            return False
        return True


class Solution_v1:
    """
    Solution v1:
        It works, but there is a lot of template code in this solution.
        The switch case statements are a bit cumbersome, how can we improve?
    """

    def isValid(self, s: str) -> bool:
        open_chars = ['(', '{', '[']
        close_chars = [')', '}', ']']
        stack = []
        for i in range(len(s)):
            if s[i] in open_chars:
                stack.append(s[i])
            elif s[i] in close_chars:
                if len(stack) == 0:
                    return False
                if s[i] == ')' and stack.pop() != '(':
                    return False
                elif s[i] == '}' and stack.pop() != '{':
                    return False
                elif s[i] == ']' and stack.pop() != '[':
                    return False
            else:   # space
                continue
        if len(stack) != 0:
            return False
        return True
