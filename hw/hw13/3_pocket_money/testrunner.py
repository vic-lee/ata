import random
import subprocess
from datetime import datetime


def test():
    input_limit = 300.00
    N = round(random.uniform(0.01, input_limit), 2)
    input_data = '{:.2f}'.format(N).encode('utf-8')

    process = subprocess.Popen(['java', 'Main'],
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)

    expected_stdout, stderr_data = process.communicate(input=input_data)
    process.kill()

    test_program = subprocess.Popen(['./main'],
                                    stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE)

    actual_stdout, stderr_data = test_program.communicate(input=input_data)
    test_program.kill()

    try:
        assert actual_stdout == expected_stdout
    except AssertionError as err:
        print(repr(input_data.decode('ascii')))
        print(f'expected:\n{repr(expected_stdout)}')
        print(f'actual:\n{repr(actual_stdout)}')
        quit()

    print(expected_stdout, actual_stdout)


if __name__ == "__main__":
    begin = datetime.now()
    test_count = 0

    while (datetime.now() - begin).seconds <= 20:
        test()
        test_count += 1

    print(f'tested {test_count} cases without error')
