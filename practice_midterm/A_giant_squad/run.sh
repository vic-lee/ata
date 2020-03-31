#!/bin/bash

for d in tests/* ; do
    ./main < "$d/input" > tmp && diff tmp "$d/output" && echo -e "$d \\tpassed" || echo -e "!!! $d \\tfailed !!!"
done