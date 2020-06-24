"""
146. LRU Cache
src: https://leetcode.com/problems/lru-cache/
"""

from collections import deque, OrderedDict


class LRUCache:
    """
    Results
    -------
    Runtime:        108ms   (85.65%)
    Memory:         21.5Mb  (94.25%)
    """

    def __init__(self, capacity: int):
        self.__CAP = capacity
        self.__map = OrderedDict()

    def get(self, key: int) -> int:
        if key in self.__map:
            self.__map.move_to_end(key)
            return self.__map[key]
        else:
            return -1

    def put(self, key: int, value: int) -> None:
        if key in self.__map:
            self.__map.move_to_end(key)
        self.__map[key] = value
        if len(self.__map) > self.__CAP:
            self.__map.popitem(last=False)


class LRUCache:
    """
    Results
    -------
    Runtime:        524ms   (8.06%)
    Memory:         216Mb   (88.40%)
    """

    def __init__(self, capacity: int):
        self.__CAP = capacity
        self.__map = {}
        self.__deq = deque()

    def get(self, key: int) -> int:
        if key in self.__map:
            self.__deq.remove(key)
            self.__deq.append(key)
            return self.__map[key]
        else:
            return -1

    def put(self, key: int, value: int) -> None:
        if key in self.__map:
            self.__deq.remove(key)
        elif len(self.__map) >= self.__CAP:
            to_remove = self.__deq.popleft()
            self.__map.pop(to_remove)
        self.__map[key] = value
        self.__deq.append(key)
