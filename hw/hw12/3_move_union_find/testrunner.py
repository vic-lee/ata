import random
import subprocess
from datetime import datetime


def gen_test():
    # input_limit = 100_000
    input_limit = 100_000
    N = random.randint(1, input_limit)
    cmd_limit = 100
    M = random.randint(1, cmd_limit)

    commands = []
    for _ in range(M):
        cmd = random.sample([1, 2, 3], 1)[0]
        if cmd == 3:
            a = random.randint(1, N)
            commands.append(f'{cmd} {a}')
        else:
            a = random.randint(1, N)
            b = random.randint(1, N)
            commands.append(f'{cmd} {a} {b}')

    input_data = f'{N} {M}\n'
    for line in commands:
        input_data += f'{line}\n'

    return input_data.encode('utf-8')


def test_program(input_data: str):
    process = subprocess.Popen(['java', 'Main'],
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)

    expected_stdout, stderr_data = process.communicate(input=input_data)
    process.kill()
    assert stderr_data == b''

    test_program = subprocess.Popen(['./main'],
                                    stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE)

    actual_stdout, stderr_data = test_program.communicate(input=input_data)
    test_program.kill()
    assert stderr_data == b''

    try:
        assert actual_stdout == expected_stdout
    except AssertionError as err:
        print(repr(input_data.decode('ascii')))
        print(f'expected:\n{repr(expected_stdout)}')
        print(f'actual:\n{repr(actual_stdout)}')
        quit()


def main():
    begin = datetime.now()
    test_count = 0

    while (datetime.now() - begin).seconds <= 60:
        input_data = gen_test()
        test_program(input_data)
        test_count += 1

    print(f'tested {test_count} cases without error')


if __name__ == "__main__":
    main()
