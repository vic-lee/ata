import os
import re
import sys


from pprint import pprint
from typing import List


def get_test_cases() -> List[List[str]]:
    def to_abs_path(fname):
        return os.path.abspath(relative_path + '/' + fname)

    def match_files(src: List[str], ptn: re.Pattern, sort=True, to_abs=True) -> List[str]:
        matched = filter(ptn.search, src)
        matched = map(to_abs_path, matched) if to_abs else matched
        return list(sorted(matched)) if sort else list(matched)

    relative_path = sys.argv[1].strip('/') if len(sys.argv) > 1 else '.'
    dir = os.listdir(relative_path)

    input_file_ptn = re.compile('\w+.in.txt')
    output_file_ptn = re.compile('\w+.out.txt')

    input_files = match_files(dir, input_file_ptn)
    output_files = match_files(dir, output_file_ptn)
    test_cases = list(zip(input_files, output_files))

    pprint(test_cases)
    return test_cases


if __name__ == '__main__':
    get_test_cases()
