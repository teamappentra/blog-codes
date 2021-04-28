set -o xtrace

ARGS="-g -O3 -march=core-avx2 -ffast-math loop-fission-unvectorizable.c -lm"
ARGS_LOW="-DLOW_INTENSITY ${ARGS}"

clang ${ARGS} -o loop-fission-clang
gcc ${ARGS} -o loop-fission-gcc
icc ${ARGS} -o loop-fission-icc

clang ${ARGS_LOW} -o loop-fission-clang-low
gcc ${ARGS_LOW} -o loop-fission-gcc-low
icc ${ARGS_LOW} -o loop-fission-icc-low


./loop-fission-clang
./loop-fission-gcc
./loop-fission-icc

./loop-fission-clang-low
./loop-fission-gcc-low
./loop-fission-icc-low
