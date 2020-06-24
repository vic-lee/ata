import random
import subprocess
from datetime import datetime


def gen_test():
    STACK_SZ_MIN = 1
    STACK_SZ_MAX = 30
    STACK_ELEM_MIN = 1
    STACK_ELEM_MAX = 100

    stack_sz = random.randint(STACK_SZ_MIN, STACK_SZ_MAX)
    stack = [str(random.randint(STACK_ELEM_MIN, STACK_ELEM_MAX))
             for _ in range(stack_sz)]
    ' '.join(stack).encode('utf-8')


def run_test(input_data: bytes):
    test_program = subprocess.Popen(['./main'],
                                    stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE)
    actual_stdout, stderr_data = test_program.communicate(input=input_data)

    try:
        assert stderr_data == b'', stderr_data
    except AssertionError as err:
        print(stderr_data)
        quit()


def main():
    begin = datetime.now()
    test_count = 0

    while (datetime.now() - begin).seconds <= 60:
        input_data = gen_test()
        run_test(input_data)
        test_count += 1

    print(f'tested {test_count} cases without error')


if __name__ == "__main__":
    main()
