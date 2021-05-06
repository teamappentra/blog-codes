#include <math.h>
#include <stdio.h>
#include "utils.h"

double rolling_average(double a[], int n) {
    int i;
    double result = 0.0;

    double time_spent;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < n; i++) {
        result += sqrt(a[i]) / n;
    }

    time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result, time_spent);

    return result;
}

double rolling_average_multi(double a[], int n) {
    int i;
    double result = 0.0;

    double time_spent;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

#pragma omp parallel default(none) shared(a, n, result) private(i)
    {
#pragma omp for reduction(+ : result) schedule(auto)
        for (i = 0; i < n; i++) {
            result += sqrt(a[i]) / n;
        }
    }  // end parallel

    time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, result, time_spent);

    return result;
}

#define ARR_LEN (100 * 1024 * 1024)

double in_arr_double[ARR_LEN];

int main(int argc, char* argv[]) {
    fill_array_double(in_arr_double, ARR_LEN);
    rolling_average(in_arr_double, ARR_LEN);
    rolling_average_multi(in_arr_double, ARR_LEN);

    return 0;
}