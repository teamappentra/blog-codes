wget --no-clobber https://www.appentra.com/wp-content/uploads/2021/01/15360_8640.zip 

unzip -o 15360_8640.zip


CC=gcc
CFLAGS="-O3 -g3 -ggdb -fopenmp -ffast-math  -fno-omit-frame-pointer"
LDFLAGS="-lm"
OMP_NUM_THREADS=8

set -o xtrace

${CC} ${CFLAGS} canny-optimized.c -o canny-optimized ${LDFLAGS}
${CC} ${CFLAGS} canny-original.c -o canny-original ${LDFLAGS}

CANNYPARAMS="testvecs/input/15360_8640.pgm 0.5 0.7 0.9"
TIMECMD="/usr/bin/time -f'%E'"
echo "Running canny-original"
set -o xtrace
${TIMECMD} ./canny-original ${CANNYPARAMS}
set +o xtrace

echo "Running canny-optimized"
set -o xtrace
${TIMECMD} ./canny-optimized ${CANNYPARAMS}
set +o xtrace
