import os
import re
import subprocess
import sys
from collections import namedtuple
from pprint import pprint
from typing import List

TestCase = namedtuple('TestCase', ['input', 'output'])


def read_args():
    relative_path = sys.argv[1].strip('/') if len(sys.argv) > 1 else '.'
    return os.path.abspath(relative_path)


def get_test_cases(target_path) -> List[TestCase]:
    def to_abs_path(fname):
        return os.path.abspath(target_path + '/' + fname)

    def match_files(src: List[str], ptn: re.Pattern, sort=True, to_abs=True) -> List[str]:
        matched = filter(ptn.search, src)
        matched = map(to_abs_path, matched) if to_abs else matched
        return list(sorted(matched)) if sort else list(matched)

    dir = os.listdir(target_path)

    input_file_ptn = re.compile('\w+.in.txt')
    output_file_ptn = re.compile('\w+.out.txt')

    input_files = match_files(dir, input_file_ptn)
    output_files = match_files(dir, output_file_ptn)
    test_cases = [TestCase(t[0], t[1])
                  for t in list(zip(input_files, output_files))]

    pprint(test_cases)
    return test_cases


def run_tests(target_abs_path, test_cases):
    print(target_abs_path)
    cpp_cmp_args = ['g++', '-std=c++11', 'main.cpp']
    comp_res = subprocess.run(cpp_cmp_args,
                              cwd=target_abs_path, capture_output=True)
    comp_errs = comp_res.stderr.decode().splitlines()
    if len(comp_errs) > 0:
        pprint(comp_errs)
        return

    for test in test_cases:
        assert os.path.isfile(test.input)
        assert os.path.isfile(test.output)

        with open(test.input, 'r') as f_in:
            test_res = subprocess.run('./a.out',
                                      cwd=target_abs_path,
                                      stdin=f_in,
                                      capture_output=True)
            test_errs = test_res.stderr.decode().splitlines()
            test_output = test_res.stdout.decode().splitlines()
            if len(test_errs) > 0:
                print(test_errs)

        with open(test.output, 'r') as f_out:
            expected_output = [l.strip() for l in f_out.readlines()]

        assert test_output == expected_output


if __name__ == '__main__':
    target_path = read_args()
    test_cases = get_test_cases(target_path)
    run_tests(target_path, test_cases)
