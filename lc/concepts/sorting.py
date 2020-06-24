'''
    This file contains an assortment of sorting algorithms,
    implemented in Python. The file is intended to be a
    practice while reading `Introduction to Algorithms`.

    Author: Vic Lee
'''

import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

fmt = '%(name)s - %(levelname)s - %(message)s'
formatter = logging.Formatter(fmt)
stream_handler = logging.StreamHandler()
stream_handler.setFormatter(formatter)

logger.addHandler(stream_handler)


def test_sort(sort_func):
    """Decorator that tests if a sorting algorithm is correct"""
    def wrapper(*args, **kwargs):
        unsorted_list = args[0]
        logger.info("unsorted: \t{}".format(unsorted_list))
        correct_sort_list = _sort_tester(*args, **kwargs)
        sorted_list = sort_func(*args, **kwargs)
        if sorted_list != correct_sort_list:
            logger.error("sorting output incorrect")
        else:
            logger.info("sorted: \t{}".format(sorted_list))

        return sorted_list

    return wrapper


def _sort_tester(nums: [int]) -> [int]:
    """Implemented in insertion sort"""
    LIST_SIZE = len(nums)
    for cur in range(LIST_SIZE):
        key = nums[cur]
        i = cur - 1
        while i >= 0 and nums[i] > key:
            nums[i + 1] = nums[i]
            i -= 1
        nums[i + 1] = key
    return nums


@test_sort
def insertion_sort(nums: [int]) -> [int]:
    '''
    Algorithm description:
        for each number in consideration, test if the number is smaller than
        the number before it. If no, then swap itself with the prior number.
        As the number of numbers considered increases, the list becomes inc-
        reasingly sorted. At the end, every number is larger or equal to the
        number before itself; the list is thus sorted. 

    Time complexity:    O(n^2)
        For each number (n), it considers, at max, on average, `n/2` numbers.
        The time needed is thus, crudely, `n^2 / 2` ==> `O(n^2)`.

    Memory complexity:  O(n)
    '''
    LIST_SIZE = len(nums)
    for cur in range(LIST_SIZE):
        key = nums[cur]
        i = cur - 1                         # start from considering the num @ cur-1
        while i >= 0 and nums[i] > key:     # if prior number is larger than key
            nums[i + 1] = nums[i]           # swap with the number before it
            i -= 1                          # if swapped, we continue consider the num before

        # At this point, the number at i+1 has been copied to i+2.
        # i.e. it is safe to overwrite the value stored at i+1. 
        #
        # Because the while loop before us has terminated, this means: 
        # EITHER we've reached the beginning of the list (the key is the
        # smallest value in the list), OR nums[i] <= key <= nums[i+1].
        # We know from the while loop that the value at i+1 (originall i, 
        # but i has been decremented) is larger than key, and is copied 
        # to i+2 (again, originally i+1). The while loop has ended, so, 
        # if the cursor is not at the front, this must mean that 
        # nums[i] <= key, terminating the while loop. 

        # We have thus shown that nums[i] <= key <= nums[i+1], provided
        # we are not at the front of the list, in which case we've shown
        # key <= nums[i+1].

        nums[i + 1] = key
    return nums


def main():
    unsorted_list = [-1, 2, 100, -3, -37, 7, 6, 99]
    sorted_list = insertion_sort(unsorted_list)


if __name__ == '__main__':
    main()
