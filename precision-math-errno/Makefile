# Run "make gcc" or "make clang", then "make run"

ARGS           = -O3 -march=core-avx2
CLANG_VEC_ARGS = -Rpass-missed=loop-vectorize -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize

.PHONY: default clean gcc clang run

default: gcc

clean:
	rm -f precision-math-errno precision-nomath-errno precision-fast-math

gcc: clean
	gcc ${ARGS} precision-math-errno.c -o precision-math-errno -lm
	gcc ${ARGS} -fno-math-errno precision-math-errno.c -o precision-nomath-errno -lm
	gcc ${ARGS} -ffast-math precision-math-errno.c -o precision-fast-math -lm

clang: clean
	clang ${CLANG_VEC_ARGS} ${ARGS} precision-math-errno.c -o precision-math-errno -lm
	clang ${CLANG_VEC_ARGS} ${ARGS} -fno-math-errno precision-math-errno.c -o precision-nomath-errno -lm
	clang ${CLANG_VEC_ARGS} ${ARGS} -ffast-math precision-math-errno.c -o precision-fast-math -lm

run:
	@echo "Without -fno-math-errno"
	./precision-math-errno

	@echo "With -fno-math-errno"
	./precision-nomath-errno

	@echo "With -ffast-math"
	./precision-fast-math
