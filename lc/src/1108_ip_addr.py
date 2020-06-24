"""
1108. Defanging an IP Address
src: https://leetcode.com/problems/defanging-an-ip-address/

This is a weird problem where I think each solution is just as good, if not as 
pythonic. The second solution is my first solution, and my favorite. I thought 
of the other solutions afterwards, partly based on the community's solutions.

Because strings are immutable in Python, there's no way of getting around 
creating a new string at the end.
"""


class Solution:
    def defangIPaddr(self, address: str) -> str:
        return "[.]".join(address.split("."))


class Solution:
    def defangIPaddr(self, address: str) -> str:
        return address.replace(".", "[.]")


class Solution:
    def defangIPaddr(self, address: str) -> str:
        return ''.join([s if s != '.' else '[.]' for s in address])


class Solution:
    def defangIPaddr(self, address: str) -> str:
        s = []
        for i in range(len(address)):
            if address[i] == '.':
                s.append('[.]')
            else:
                s.append(address[i])
        return ''.join(s)


class Solution:
    def defangIPaddr(self, address: str) -> str:
        s = ''
        for i in range(len(address)):
            if address[i] == '.':
                s += '[.]'
            else:
                s += address[i]
        return s
