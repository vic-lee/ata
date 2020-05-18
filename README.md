# APS

This repository contains all the coursework for class Algorithmic Problem
Solving (APS).

All the problem prompts are stored in the `problems` folder. All other
directories refer to implementation source code.

Folder `ds`, in particular, contains custom data structures implemented to
solve problems for this class.

## Getting started

Most problem folders contain test cases. Use `run.sh` to test the source file.

For instance, to test problem #1 in homework 10, run the following command from 
the project root:

```shell
$ ./run.sh hw/hw10/1_bus_tour
Compiling hw/hw10/1_bus_tour/main.cpp...
Using binary 'main' to run tests in hw/hw10/1_bus_tour/tests
hw/hw10/1_bus_tour/tests/1      passed
hw/hw10/1_bus_tour/tests/2      passed
hw/hw10/1_bus_tour/tests/3c     passed
hw/hw10/1_bus_tour/tests/4c     passed
hw/hw10/1_bus_tour/tests/5c     passed
hw/hw10/1_bus_tour/tests/6c     passed
hw/hw10/1_bus_tour/tests/7c     passed
```

The source file is assumed to use the name `main.cpp`, under the implementation
directory specified. If that is not the case, and an executable named `main` is
not found, the script will fail. It is possible to override the name of the
executable used, which is often useful for testing Java programs. Refer to
the documentation in `run.sh` for more detail.

A canonical `tests` folder for a problem is structured like so:

```
hw/hw10/1_bus_tour/tests
├── 1
│   ├── input
│   └── output
├── 2
│   ├── input
│   └── output
├── 3c
│   ├── input
│   └── output
├── ...
└── 7c
    ├── input
    └── output
```

Each subfolder in `tests` represent a test case, where `input` is the input
directed to the `stdin` for the program and `output` is the expected output from
the program. Test cases are numbered in ascending order. The `c` suffix in some
tests' names indicate it is a custom test case created for additional testing;
these tests are not provided by the problem statement and have a higher chance
of containing errors.