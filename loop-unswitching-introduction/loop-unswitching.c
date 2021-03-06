#include <stdbool.h>
#include <stdio.h>
#include "utils.h"

/* Manual loop unswitching example */
int calculate_sum(int* a, int n, bool only_positives) {
    int sum = 0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++) {
        if (only_positives) {
            if (a[i] > 0) {
                sum += a[i];
            }
        } else {
            sum += a[i];
        }
    }

    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, sum,
           get_runtime(start));

    return sum;
}

int calculate_sum_unswitched_manually(int* a, int n, bool only_positives) {
    int sum = 0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (only_positives) {
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                sum += a[i];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            sum += a[i];
        }
    }

    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, sum,
           get_runtime(start));

    return sum;
}

/** Pointer aliasing example */
#define MAX_SETTINGS_COUNT 100
#define ONLY_POSITIVES 21

bool settings[MAX_SETTINGS_COUNT];

void increment_array(int* a, int n) {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++) {
        if (settings[ONLY_POSITIVES]) {
            if (a[i] > 0) {
                a[i]++;
            }
        } else {
            a[i]++;
        }
    }

    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, a[0] + a[n - 1],
           get_runtime(start));
}

/* Function call making the loop condition not invariant example */
bool only_positives = false;

int calculate(int a) {
    if (a < 0) {
        only_positives = true;
    }
    return a;
}

int calculate_sum_call_other(int* a, int n) {
    int sum = 0;

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++) {
        if (only_positives) {
            if (a[i] > 0) {
                sum += calculate(a[i]);
            }
        } else {
            sum += calculate(a[i]);
        }
    }

    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, sum,
           get_runtime(start));

    return sum;
}

#define ARR_LEN (200 * 1024 * 1024)

int data[ARR_LEN];

int main(int argc, char** argv) {
    fill_int_array(data, ARR_LEN);

    bool arr[] = {false, true};

    for (int i = 0; i < arr_len(arr); i++) {
        only_positives = arr[i];
        settings[ONLY_POSITIVES] = arr[i];

        calculate_sum(data, ARR_LEN, arr[i]);
        calculate_sum_unswitched_manually(data, ARR_LEN, arr[i]);
        calculate_sum_call_other(data, ARR_LEN);
        increment_array(data, ARR_LEN);
    }

    return 0;
}
