#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill_array(int a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (int)rand();
        if (a[i] % 2 == 0) {
            a[i] = -a[i];
        }
    }
}

void normalize_array_to_80_percent_positive(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int val = rand() % 5;
        if (val == 0) {
            a[i] = -abs(a[i]);
        } else {
            a[i] = abs(a[i]);
        }
    }
}

void fill_histogram_array(int a[], int n, int max) {
    for (int i = 0; i < n; i++) {
        a[i] = (int)rand() % max;
    }
}

void calculate_hysteresis(int cond[], int in[], int n, int out[]) {
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 0; i < n; i++) {
        if (cond[i] > 0) {
            out[in[i]]++;
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, out[0] + out[1],
           time_spent);
}

void calculate_hysteresis_branchless(int cond[], int in[], int n, int out[]) {
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 0; i < n; i++) {
        out[in[i]] += (cond[i] > 0);
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, out[0] + out[1],
           time_spent);
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

void multiply_matrices(int c[][MATRIX_DIM],
                       int a[][MATRIX_DIM],
                       int b[][MATRIX_DIM]) {
    clock_t begin = clock(), end;
    double time_spent;

    const int n = MATRIX_DIM;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, 0, time_spent);
}

void multiply_matrices_interchanged(int c[][MATRIX_DIM],
                                    int a[][MATRIX_DIM],
                                    int b[][MATRIX_DIM]) {
    clock_t begin = clock(), end;
    double time_spent;

    const int n = MATRIX_DIM;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
        }
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, 0, time_spent);
}

void matrix_transpose(int b[][LARGE_MATRIX_DIM], int a[][LARGE_MATRIX_DIM]) {
    clock_t begin = clock(), end;
    double time_spent;

    const int n = LARGE_MATRIX_DIM;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = a[j][i];
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, 0, time_spent);
}

void matrix_transpose_tiled(int b[][LARGE_MATRIX_DIM],
                            int a[][LARGE_MATRIX_DIM]) {
    clock_t begin = clock(), end;
    double time_spent;

    const int n = LARGE_MATRIX_DIM;

    for (int ii = 0; ii < n; ii += 4) {
        for (int jj = 0; jj < n; jj += 4) {
            for (int i = ii; i < (ii + 4); i++) {
                for (int j = jj; j < (jj + 4); j++) {
                    b[i][j] = a[j][i];
                }
            }
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, 0, time_spent);
}

void print_matrix(int m[][LARGE_MATRIX_DIM]) {
    const int n = LARGE_MATRIX_DIM;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d, ", m[i][j]);
        }
        printf("\n");
    }
}

void fill_array_double(double a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (double)rand();
    }
}

double rolling_average(double a[], int n) {
    int i;
    double result = 0.0;

    clock_t begin = clock(), end;
    double time_spent;

    for (i = 0; i < n; i++) {
        result += sqrt(a[i]) / n;
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result, time_spent);

    return result;
}

double rolling_average_multi(double a[], int n) {
    int i;
    double result = 0.0;

    clock_t begin = clock(), end;
    double time_spent;

#pragma omp parallel default(none) shared(a, n, result) private(i)
    {
#pragma omp for reduction(+ : result) schedule(auto)
        for (i = 0; i < n; i++) {
            result += sqrt(a[i]) / n;
        }
    }  // end parallel

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result, time_spent);

    return result;
}

double rolling_average_offload(double a[], int n) {
    int i;
    double result = 0.0;

    clock_t begin = clock(), end;
    double time_spent;

#pragma acc data copyin(a [0:n], n) copy(result)
    {
#pragma acc parallel
        {
#pragma acc loop reduction(+ : result)
            for (i = 0; i < n; i++) {
                result += sqrt(a[i]) / n;
            }
        }  // end parallel
    }      // end data

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result, time_spent);

    return result;
}

#define ARR_LEN (100 * 1024 * 1024)
#define HIST_LEN (32768)

int in_arr[ARR_LEN];
int out_arr[ARR_LEN];

int hist_arr[HIST_LEN];
int hist_arr2[HIST_LEN];

#define SMALL_HIST_LEN 256
#define LARGE_HIST_LEN (8 * 1024 * 1024)

int in_mat1[MATRIX_DIM][MATRIX_DIM];
int in_mat2[MATRIX_DIM][MATRIX_DIM];
int out_mat1[MATRIX_DIM][MATRIX_DIM];
int out_mat2[MATRIX_DIM][MATRIX_DIM];

int in_large_mat1[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];
int out_large_mat1[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];
int out_large_mat2[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];

int main(int argc, char** argv) {
    fill_array(in_arr, ARR_LEN);

    fill_histogram_array(out_arr, ARR_LEN,
                         sizeof(hist_arr) / sizeof(hist_arr[0]));

    printf("The element of in[i] have 50%% chance of being positive\n");
    memset(hist_arr, 0, sizeof(hist_arr));
    calculate_hysteresis(in_arr, out_arr, ARR_LEN, hist_arr);

    memset(hist_arr2, 0, sizeof(hist_arr2));
    calculate_hysteresis_branchless(in_arr, out_arr, ARR_LEN, hist_arr2);

    // fill_matrix_regular(in_mat1);
    // fill_matrix_regular(in_mat2);

    // multiply_matrices(out_mat1, in_mat1, in_mat2);
    // multiply_matrices_interchanged(out_mat2, in_mat1, in_mat2);

    // compare_matrices_regular(out_mat1, out_mat2);

    // fill_matrix_large(in_large_mat1);

    // matrix_transpose(out_large_mat1, in_large_mat1);
    // matrix_transpose_tiled(out_large_mat2, in_large_mat1);

    // compare_matrices_large(out_large_mat1, out_large_mat2);

    double* in_arr_double = malloc(ARR_LEN * sizeof(double));

    fill_array_double(in_arr_double, ARR_LEN);
    rolling_average(in_arr_double, ARR_LEN);
    rolling_average_multi(in_arr_double, ARR_LEN);
    rolling_average_offload(in_arr_double, ARR_LEN);

    free(in_arr_double);

    return 0;
}