import sys


def main():
    A = []

    with open('./primes.txt') as fp:
        lines = fp.readlines()
        A = map(lambda l: int(l), lines)

    lower = int(sys.argv[1])
    upper = int(sys.argv[2])

    min_gap = 100000000
    max_gap = 0
    min_gap_lower = None
    min_gap_upper = None
    max_gap_lower = None
    max_gap_upper = None
    prev = None

    A = filter(lambda e: e >= lower and e <= upper, A)
    # print(A)

    for cur in A:
        if cur and prev:
            cur_gap = cur - prev
            if cur_gap < min_gap:
                min_gap = cur_gap
                min_gap_lower, min_gap_upper = prev, cur
            elif cur_gap > max_gap:
                max_gap = cur_gap
                max_gap_lower, max_gap_upper = prev, cur
        prev = cur

    print(min_gap_lower, min_gap_upper, max_gap_lower, max_gap_upper)


if __name__ == '__main__':
    main()
