set -e

echo "compiling..."

g++ -std=c++17 -I ../../ main.cpp ../../graph.cpp -o main

echo "compiled"

for d in ./tests/*; do
    ./main <"$d/input" >./.tmp &&
        diff ./.tmp "$d/output" &&
        echo -e "$d \\tpassed" ||
        echo -e "!!! $d \\tfailed !!!\n"
done

rm -f ./.tmp
