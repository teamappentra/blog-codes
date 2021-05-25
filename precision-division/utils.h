#pragma once

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

static void fill_int_array(int* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() - 10000;
    }
}



void fill_array_double(double a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (double)rand();
    }
}


void fill_array_float(float a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (float)rand();
    }
}

#define arr_len(x) (sizeof(x) / sizeof(x[0]))
