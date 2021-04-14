set -o xtrace

ARGS="-g -O3 -march=core-avx2 -fno-math-errno -Rpass-missed=loop-vectorize -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize"
ARGS="-g -O3 -march=core-avx2 -fno-math-errno"
CC=clang
${CC} ${ARGS} precision-omp-simd.c -o precision-noomp-simd  -lm
${CC} ${ARGS} -fopenmp precision-omp-simd.c -o precision-omp-simd -lm

echo "Without -fopenmp"
./precision-noomp-simd

echo "With OpenMP vectorization"
./precision-omp-simd