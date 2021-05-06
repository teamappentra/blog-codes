#include <stdio.h>
#include "utils.h"

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

int in_large_mat1[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];
int out_large_mat1[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];
int out_large_mat2[LARGE_MATRIX_DIM][LARGE_MATRIX_DIM];

int main(int argc, char** argv) {
    fill_matrix_large(in_large_mat1);

    matrix_transpose(out_large_mat1, in_large_mat1);
    matrix_transpose_tiled(out_large_mat2, in_large_mat1);

    compare_matrices_large(out_large_mat1, out_large_mat2);
}