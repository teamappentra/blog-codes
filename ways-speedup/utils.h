#include <stdlib.h>
#include <time.h>

double get_runtime(struct timespec start) {
    struct timespec finish;
    double seconds;

    clock_gettime(CLOCK_MONOTONIC, &finish);

    seconds = (finish.tv_sec - start.tv_sec);
    seconds += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    return seconds;
}

#define MATRIX_DIM (2400)
#define LARGE_MATRIX_DIM (10000)

#define FILL_MATRIX(name, dimension)              \
    void fill_matrix_##name(int m[][dimension]) { \
        for (int i = 0; i < dimension; i++) {     \
            for (int j = 0; j < dimension; j++) { \
                m[i][j] = rand();                 \
            }                                     \
        }                                         \
    }

FILL_MATRIX(regular, MATRIX_DIM)
FILL_MATRIX(large, LARGE_MATRIX_DIM)

#define COMPARE_MATRIX(name, dimension)                                      \
    void compare_matrices_##name(int m1[][dimension], int m2[][dimension]) { \
        int same = 1;                                                        \
        for (int i = 0; i < dimension; i++) {                                \
            for (int j = 0; j < dimension; j++) {                            \
                if (m1[i][j] != m2[i][j]) {                                  \
                    same = 0;                                                \
                    break;                                                   \
                }                                                            \
            }                                                                \
        }                                                                    \
                                                                             \
        if (same) {                                                          \
            printf("Matrices same\n");                                       \
        } else {                                                             \
            printf("Matrices different\n");                                  \
        }                                                                    \
    }

COMPARE_MATRIX(regular, MATRIX_DIM)
COMPARE_MATRIX(large, LARGE_MATRIX_DIM)

void fill_array(int a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (int)rand();
        if (a[i] % 2 == 0) {
            a[i] = -a[i];
        }
    }
}

void fill_array_double(double a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (double)rand();
    }
}

void fill_histogram_array(int a[], int n, int max) {
    for (int i = 0; i < n; i++) {
        a[i] = (int)rand() % max;
    }
}
