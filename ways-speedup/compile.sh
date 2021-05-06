set -o xtrace

CC="clang -fopenmp -O3 -g -lm"

${CC} branch-prediction-example.c -o branch-prediction-example
${CC} memory-example.c -o memory-example
${CC} multithreading-example.c -o multithreading-example
${CC} vectorization-example.c -o vectorization-example

nvc -acc -O3 -g accelerator-example.c -o accelerator-example -lm

./multithreading-example
./accelerator-example
./vectorization-example
./memory-example
./branch-prediction-example
