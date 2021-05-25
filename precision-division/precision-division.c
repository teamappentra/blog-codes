#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

double rolling_average(double a[], int n) {
    int i;
    double result = 0.0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

#pragma omp simd reduction(+ : result)
    for (i = 0; i < n; i++) {
        result += sqrt(a[i]) / n;
    }

    printf("%s: Result = %.17g, runtime = %f\n", __FUNCTION__, result,
           get_runtime(start));

    return result;
}

double rolling_average_recip(double a[], int n) {
    int i;
    double result = 0.0;
    double n_recip = 1.0 / n;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

#pragma omp simd reduction(+ : result)
    for (i = 0; i < n; i++) {
        result += sqrt(a[i]) * n_recip;
    }

    printf("%s: Result = %.17g, runtime = %f\n", __FUNCTION__, result,
           get_runtime(start));

    return result;
}

void division(float a[], float b[], float c[], int n) {
    float sum = 0.0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++) {
        c[i] = a[i] / b[i];
    }

    printf("%s: Result = %.17g, runtime = %f\n", __FUNCTION__, c[0],
           get_runtime(start));
}

#define VECTOR_SIZE 8
typedef
    __attribute((vector_size(32))) float v8sf;  // vector of four single floats

void division_approximate(float a[], float b[], float c[], int n) {
    v8sf* a_vec = (v8sf*)a;
    v8sf* b_vec = (v8sf*)b;
    v8sf* c_vec = (v8sf*)c;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n / VECTOR_SIZE; i++) {
        v8sf b_recip = __builtin_ia32_rcpps256(b_vec[i]);
        c_vec[i] = a_vec[i] * b_recip;
        // c_vec[i] = a_vec[i] / b_vec[i];
    }

    for (int i = n / VECTOR_SIZE; i < n; i++) {
        c[i] = a[i] / b[i];
    }

    printf("%s: Result = %.17g, runtime = %f\n", __FUNCTION__, c[0],
           get_runtime(start));
}

void compare_arrays(float a[], float b[], int n) {
#define COUNT 11
    int histogram[COUNT];
    float cut_values[COUNT - 1] = {0.00000001f, 0.0000001f, 0.000001f, 0.00001f,
                                   0.0001f,     0.001f,     0.01f,     0.1f,
                                   1.0f,        10.0f};

    memset(histogram, 0, sizeof(histogram));
    for (int i = 0; i < n; i++) {
        int found = 0;
        float diff = fabsf(a[i] - b[i]);

        for (int j = 0; j < COUNT - 1; j++) {
            if (diff < cut_values[j]) {
                found = 1;
                histogram[j]++;
                break;
            }
        }

        if (!found) {
            histogram[COUNT - 1]++;
        }
    }

    printf("Histograms\n");
    for (int i = 0; i < COUNT - 1; i++) {
        printf("< %f: %d, %f %%\n", cut_values[i], histogram[i],
               (double)histogram[i] / n * 100);
    }
    printf("> %f: %d, %f %%\n", cut_values[COUNT - 2], histogram[COUNT - 1],
           (double)histogram[COUNT - 1] / n * 100);
}

#define ARR_LEN (256 * 1024 * 1024)

int main(int argc, char** argv) {
    int arr_len = ARR_LEN;
    float *a, *b, *c, *c_approx;
    double* arr_double;

    if (argc >= 2) {
        arr_len = atoi(argv[1]);
        if (arr_len == 0) {
            arr_len = ARR_LEN;
        }
    }

    arr_double = malloc(sizeof(double) * arr_len);
    fill_array_double(arr_double, arr_len);

    printf("Array length = %d\n", arr_len);

    rolling_average(arr_double, arr_len);
    rolling_average_recip(arr_double, arr_len);

    free(arr_double);
    a = aligned_alloc(64, sizeof(float) * arr_len);
    b = aligned_alloc(64, sizeof(float) * arr_len);
    c = aligned_alloc(64, sizeof(float) * arr_len);
    c_approx = aligned_alloc(64, sizeof(float) * arr_len);

    fill_array_float(a, arr_len);
    fill_array_float(b, arr_len);

    division(a, b, c, arr_len);
    division_approximate(a, b, c_approx, arr_len);

    compare_arrays(c, c_approx, arr_len);

    free(a);
    free(b);
    free(c);
    free(c_approx);

    return 0;
}
