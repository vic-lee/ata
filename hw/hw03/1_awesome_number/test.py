import sys


def main():
    A = []

    with open('../2_prime_gap/primes.txt') as fp:
        lines = fp.readlines()
        A = map(lambda l: int(l), lines)

    upper = int(sys.argv[1])
    out = filter(lambda a: a < upper and a % 10 == 1, A)
    for o in out:
        print(o)
    print("\n")
    print(len(out))


if __name__ == '__main__':
    main()
