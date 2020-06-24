class Solution_v2:
    """A much more elegant solution. Sample 40ms."""

    def moveZeroes(self, nums: List[int]) -> None:
        cur = 0
        # for each non-zero element, write them to the front area of the list
        for i in range(len(nums)):
            if nums[i] != 0:
                nums[cur] = nums[i]
                cur += 1
        # flush the remaining list elements to zero
        for i in range(cur, len(nums)):
            nums[i] = 0


class Solution_v1:
    """
    Original solution. 64ms, faster than 33.4%.

    While I knew this solution is not particularly fast (because it requires 
    many shifts in array), I could not think of a better solution. The faster 
    solution above is much more elegant.
    """

    def moveZeroes(self, nums: List[int]) -> None:
        if len(nums) == 0:
            return
        head = 0
        tail = 0
        while head < len(nums) - 1:
            # has yet to encounter 0
            if head == tail and nums[head] != 0:
                head, tail = head+1, tail+1
                continue
            # encounters a new zero
            if nums[head] == 0:
                # head moves to one before the next first non-zero position
                while (head + 1) < len(nums) and nums[head+1] == 0:
                    head += 1
                # if there's at least one element after head (which we know is
                # not a zero), we swap with the tail's position
                if head + 1 < len(nums):
                    nums[head+1], nums[tail] = nums[tail], nums[head+1]
                    # knowing head+1 is now a zero (because we just swapped
                    # nums[tail] to head+1), we increment head and tail
                    head, tail = head+1, tail+1
        if nums[-1] != 0:
            nums[-1], nums[tail] = nums[tail], nums[-1]
