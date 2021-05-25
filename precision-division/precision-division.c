#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

double rolling_average(double a[], int n) {
    int i;
    double result = 0.0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    #pragma omp simd reduction(+:result)
    for (i = 0; i < n; i++) {
        result += a[i] / n;
    }

    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result,
           get_runtime(start));

    return result;
}


double rolling_average_recip(double a[], int n) {
    int i;
    double result = 0.0;
    double n_recip = 1.0 / n;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    #pragma omp simd reduction(+:result)
    for (i = 0; i < n; i++) {
        result += a[i] * n_recip;
    }

    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result,
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

    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, c[0],
           get_runtime(start));
}

#define VECTOR_SIZE         8
typedef __attribute((vector_size(32))) float v8sf; // vector of four single floats

/*void division_approximate(float a[], float b[], float c[], int n) {
    v8sf* a_vec = (v8sf*) a;
    v8sf* b_vec = (v8sf*) b;
    v8sf* c_vec = (v8sf*) c;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n / VECTOR_SIZE; i++) {
        v8sf b_recip = __builtin_ia32_rcpps256(b_vec[i]);
        c_vec[i] = a_vec[i] * b_recip;
        //c_vec[i] = a_vec[i] / b_vec[i];
    }

    for (int i = n / VECTOR_SIZE; i < n; i++) {
        c[i] = a[i] / b[i];
    }

    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, c[0],
           get_runtime(start));
}*/

#include <immintrin.h>

void division_approximate(float a[], float b[], float c[], int n) {
    v8sf* a_vec = (v8sf*) a;
    v8sf* b_vec = (v8sf*) b;
    v8sf* c_vec = (v8sf*) c;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i+=VECTOR_SIZE) {
        __m256 b_val = _mm256_loadu_ps(b + i);
        b_val = _mm256_rcp_ps(b_val);
        __m256 a_val = _mm256_loadu_ps(a + i);
        a_val = _mm256_mul_ps(a_val, b_val);
        //a_val = _mm256_div_ps(a_val, b_val);
        _mm256_storeu_ps(c + i, a_val);
    }

    for (int i = n / VECTOR_SIZE; i < n; i++) {
        c[i] = a[i] / b[i];
    }

    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, c[0],
           get_runtime(start));
}

void compare_arrays(float a[], float b[], int n) {
#define COUNT 11
    int histogram[COUNT];
    float cut_values[COUNT - 1] = {0.00000001f, 0.0000001f, 0.000001f, 0.00001f, 0.0001f, 0.001f, 0.01f, 0.1f, 1.0f, 10.0f};

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
        printf("< %f: %d, %f %%\n", cut_values[i], histogram[i], (double) histogram[i] / n * 100);
    }
    printf("> %f: %d, %f %%\n", cut_values[COUNT - 2], histogram[COUNT - 1], (double) histogram[COUNT - 1] / n * 100);
}

#define ARR_LEN (100 * 1024 * 1024)

double arr_double[ARR_LEN];

float a[ARR_LEN];
float b[ARR_LEN];
float c[ARR_LEN];
float c_approx[ARR_LEN];


int main(int argc, char** argv) {
    fill_array_double(arr_double, ARR_LEN);

    double res;

    res = rolling_average(arr_double, ARR_LEN);
    printf("Rolling average %f\n", res);

    res = rolling_average_recip(arr_double, ARR_LEN);
    printf("Rolling average %f\n", res);

    fill_array_float(a, ARR_LEN);
    fill_array_float(b, ARR_LEN);

    division(a, b, c, ARR_LEN);

    division_approximate(a, b, c_approx, ARR_LEN);

    compare_arrays(c, c_approx, ARR_LEN);

    return 0;
}