wget --no-clobber https://www.appentra.com/wp-content/uploads/2021/01/15360_8640.zip 

unzip -o 15360_8640.zip


CC=clang
CFLAGS="-O3 -ffast-math -g -lm -fno-omit-frame-pointer"

${CC} ${CFLAGS} canny-optimized.c -o canny-optimized
${CC} ${CFLAGS} canny-original.c -o canny-original

CANNYPARAMS="testvecs/input/15360_8640.pgm 0.5 0.7 0.9"
TIMECMD="/usr/bin/time -f'%E'"
echo "Running canny-original"
${TIMECMD} ./canny-original ${CANNYPARAMS}

echo "Running canny-optimized"
${TIMECMD} ./canny-optimized ${CANNYPARAMS}
