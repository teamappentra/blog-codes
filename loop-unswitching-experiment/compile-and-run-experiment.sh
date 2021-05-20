#!/bin/bash

COMPILATION_LINE="-O3 loop-unswitching-experiment.c -o loop-unswitching-experiment"
LINK_LINE="-lm"

clang ${COMPILATION_LINE}-clang ${LINK_LINE}
gcc ${COMPILATION_LINE}-gcc ${LINK_LINE}
icc ${COMPILATION_LINE}-icc ${LINK_LINE}

compilers=("gcc" "clang" "icc")

for array_operation in {0..2}; do
    for single_operation in {0..3}; do
        for set_b in {0..1}; do
            for compiler in "${compilers[@]}"; do
                ./loop-unswitching-experiment-${compiler} ${array_operation} ${single_operation} ${set_b} 
            done
        done
    done
done
