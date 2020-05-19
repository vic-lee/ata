import sys
import re


def read_in():
    raw_txt = []
    for line in sys.stdin:
        raw_txt.append(line.strip())
    return raw_txt


def to_words(lines):
    words = []
    src = [re.findall(r'\w+', line) for line in lines]
    for s in src:
        words += list(map(lambda w: w.lower(), s))
    return words


def problem(raw_txt):
    words = to_words(raw_txt)
    return sorted(set(words))


if __name__ == '__main__':
    raw_txt = read_in()
    words = problem(raw_txt)
    for w in words:
        print(w)
