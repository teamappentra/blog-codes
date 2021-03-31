set -o xtrace

ARGS="-g -O3 -march=core-avx2 -Rpass-missed=loop-vectorize -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize"
ARGS="-g -O3 -march=core-avx2"
CC=gcc
${CC} ${ARGS} precision-math-errno.c -o precision-math-errno  -lm
${CC} ${ARGS} -fno-math-errno precision-math-errno.c -o precision-nomath-errno -lm

echo "Without -fno-math-errno"
./precision-math-errno

echo "With -fno-math-errno"
./precision-nomath-errno
