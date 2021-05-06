#include <stdio.h>
#include "utils.h"

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

int in_mat1[MATRIX_DIM][MATRIX_DIM];
int in_mat2[MATRIX_DIM][MATRIX_DIM];
int out_mat1[MATRIX_DIM][MATRIX_DIM];
int out_mat2[MATRIX_DIM][MATRIX_DIM];

int main(int argc, char** argv) {
    fill_matrix_regular(in_mat1);
    fill_matrix_regular(in_mat2);

    multiply_matrices(out_mat1, in_mat1, in_mat2);
    multiply_matrices_interchanged(out_mat2, in_mat1, in_mat2);

    compare_matrices_regular(out_mat1, out_mat2);

    return 0;
}