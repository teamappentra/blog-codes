#pragma once

#include <stdbool.h>
#include <stdio.h>
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

#define ARRAY_OPERATIONS(V) \
    V(ADD)                  \
    V(SUBTRACT)             \
    V(REPLACE)

#define SINGLE_OPERATIONS(V) \
    V(ADD_SUB)               \
    V(MUL_DIV)               \
    V(SIN_COS)               \
    V(SQRT_ABS)

enum array_operation_e {
#define ARRAY_OPERATION_ENUM(x) x,
    ARRAY_OPERATIONS(ARRAY_OPERATION_ENUM)
#undef ARRAY_OPERATION_ENUM
};

enum single_operation_e {
#define SINGLE_OPERATION_ENUM(x) x,
    SINGLE_OPERATIONS(SINGLE_OPERATION_ENUM)
#undef SINGLE_OPERATION_ENUM
};

const char* array_operation_to_string(enum array_operation_e e) {
    switch (e) {
#define ARRAY_OPERATION_TO_STRING(x) \
    case x:                          \
        return #x;
        ARRAY_OPERATIONS(ARRAY_OPERATION_TO_STRING)
#undef ARRAY_OPERATION_TO_STRING
        default:
            return "UNKNOWN";
    };
}

const char* single_operation_to_string(enum single_operation_e e) {
    switch (e) {
#define SINGLE_OPERATION_TO_STRING(x) \
    case x:                           \
        return #x;
        SINGLE_OPERATIONS(SINGLE_OPERATION_TO_STRING)
#undef SINGLE_OPERATION_TO_STRING
    }
}

static void fill_array(float* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() - 10000;
    }
}

static void fill_int_array(int* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() - 10000;
    }
}

static int compare_arrays(float* a, float* b, int n) {
    int count_different = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count_different++;
        }
    }

    return count_different;
}

const char* bool_to_string(bool b) {
    return b ? "true" : "false";
}

static void print_array(float* a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f, ", a[i]);
    }
    printf("\n");
}

const char* get_compiler_string() {
    const char* compiler_string;
#if defined __INTEL_COMPILER
    return "INTEL";
#elif defined(__clang__)
    return "CLANG";
#elif defined(__GNUC__) || defined(__GNUG__)
    return "GCC";
#else
    return "UNKNOWN";
#endif
}

#define arr_len(x) (sizeof(x) / sizeof(x[0]))
