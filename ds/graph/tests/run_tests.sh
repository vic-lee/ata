set -e

run_test_in_dir() {
    dir=$1

    echo "\ncompiling test for \`$dir\`..."

    g++ -std=c++17 -I ../ "./$dir/main.cpp" ../graph.cpp -o "./$dir/main"

    echo "compiled"

    for d in ./$dir/tests/*; do
        ./$dir/main <"$d/input" >./$dir/.tmp &&
            diff ./$dir/.tmp "$d/output" &&
            echo "-> $d \\tpassed" ||
            echo "!!! $d \\tfailed !!!\n"
    done

    rm -f ./$dir/.tmp
}

# Supply an argument to run tests in that directory
# or run all test suites in the subdirectories.
if [ -z "$1" ]; then
    for test_dir in ./*/; do run_test_in_dir $test_dir; done
else
    run_test_in_dir $1
fi
