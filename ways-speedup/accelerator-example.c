#include <math.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

double calculate_pi(int N) {
    double time_spent;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    double out_result;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) / N;
        sum += sqrt(1 - x * x);
    }

    out_result = 4.0 / N * sum;

    time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, out_result,
           time_spent);

    return out_result;
}

double calculate_pi_offload(int N) {
    double time_spent;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    double out_result;
    double sum = 0.0;

#pragma acc data copyin(N) copy(sum)
    {
#pragma acc parallel
        {
#pragma acc loop reduction(+ : sum)
            for (int i = 0; i < N; i++) {
                double x = (i + 0.5) / N;
                sum += sqrt(1 - x * x);
            }
        }  // end parallel
    }      // end data

    out_result = 4.0 / N * sum;

    time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__, out_result,
           time_spent);

    return out_result;
}

int main(int argc, char** argv) {
    const int pi_size = 2000 * 1000 * 1000;

    calculate_pi(pi_size);
    calculate_pi_offload(pi_size);

    return 0;
}
