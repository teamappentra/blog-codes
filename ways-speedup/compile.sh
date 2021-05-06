clang -fopenmp -O3 -g many-ways.c -o many-ways -lm
nvc -acc -O3 -g many-ways-gpu.c -o many-ways-gpu -lm

./many-ways
./many-ways-gpu
