#pragma once

#include <math.h>
#include "utils.h"

extern enum single_operation_e single_operation;
extern enum array_operation_e array_operation;

#define SINGLE_CALCULATION(operation, set_out2)       \
    void single_calculation_##operation##_##set_out2( \
        int in1, int in2, float* out1, float* out2) { \
        switch (operation) {                          \
            case ADD_SUB:                             \
                *out1 = in1 + in2;                    \
                if (set_out2) {                       \
                    *out2 = in1 - in2;                \
                }                                     \
                break;                                \
            case MUL_DIV:                             \
                *out1 = in1 * in2;                    \
                if (set_out2) {                       \
                    *out2 = in1 / (in2 + (in2 == 0)); \
                }                                     \
                break;                                \
            case SIN_COS:                             \
                *out1 = sinf(in1);                    \
                if (set_out2) {                       \
                    *out2 = cosf(in1);                \
                }                                     \
                break;                                \
            case SQRT_ABS:                            \
                *out1 = abs(in1);                     \
                if (set_out2) {                       \
                    *out2 = sqrt(abs(in2));           \
                }                                     \
                break;                                \
        }                                             \
    }

SINGLE_CALCULATION(ADD_SUB, true)
SINGLE_CALCULATION(ADD_SUB, false)
SINGLE_CALCULATION(MUL_DIV, true)
SINGLE_CALCULATION(MUL_DIV, false)
SINGLE_CALCULATION(SIN_COS, true)
SINGLE_CALCULATION(SIN_COS, false)
SINGLE_CALCULATION(SQRT_ABS, true)
SINGLE_CALCULATION(SQRT_ABS, false)

#define ARRAY_CALCULATION(array_operation, single_operation, set_b)          \
    void array_calculation_##array_operation##_##single_operation##_##set_b( \
        float* a, float* b, int n) {                                         \
        float r1, r2;                                                        \
        for (int i = 0; i < n; i++) {                                        \
            single_calculation_##single_operation##_##set_b(i, i + 1, &r1,   \
                                                            &r2);            \
            if (array_operation == ADD) {                                    \
                a[i] += r1;                                                  \
                if (set_b) {                                                 \
                    b[i] += r2;                                              \
                }                                                            \
            } else if (array_operation == SUBTRACT) {                        \
                a[i] -= r1;                                                  \
                if (set_b) {                                                 \
                    b[i] -= r2;                                              \
                }                                                            \
            } else {                                                         \
                a[i] = r1;                                                   \
                if (set_b) {                                                 \
                    b[i] = r2;                                               \
                }                                                            \
            }                                                                \
        }                                                                    \
    }

ARRAY_CALCULATION(ADD, ADD_SUB, true)
ARRAY_CALCULATION(ADD, ADD_SUB, false)
ARRAY_CALCULATION(ADD, MUL_DIV, true)
ARRAY_CALCULATION(ADD, MUL_DIV, false)
ARRAY_CALCULATION(ADD, SIN_COS, true)
ARRAY_CALCULATION(ADD, SIN_COS, false)
ARRAY_CALCULATION(ADD, SQRT_ABS, true)
ARRAY_CALCULATION(ADD, SQRT_ABS, false)
ARRAY_CALCULATION(SUBTRACT, ADD_SUB, true)
ARRAY_CALCULATION(SUBTRACT, ADD_SUB, false)
ARRAY_CALCULATION(SUBTRACT, MUL_DIV, true)
ARRAY_CALCULATION(SUBTRACT, MUL_DIV, false)
ARRAY_CALCULATION(SUBTRACT, SIN_COS, true)
ARRAY_CALCULATION(SUBTRACT, SIN_COS, false)
ARRAY_CALCULATION(SUBTRACT, SQRT_ABS, true)
ARRAY_CALCULATION(SUBTRACT, SQRT_ABS, false)
ARRAY_CALCULATION(REPLACE, ADD_SUB, true)
ARRAY_CALCULATION(REPLACE, ADD_SUB, false)
ARRAY_CALCULATION(REPLACE, MUL_DIV, true)
ARRAY_CALCULATION(REPLACE, MUL_DIV, false)
ARRAY_CALCULATION(REPLACE, SIN_COS, true)
ARRAY_CALCULATION(REPLACE, SIN_COS, false)
ARRAY_CALCULATION(REPLACE, SQRT_ABS, true)
ARRAY_CALCULATION(REPLACE, SQRT_ABS, false)

void array_calculation_unswitched(float* a, float* b, int n, bool set_b) {
#define CALL(arr_op, single_op, set_b_v)                               \
    if (array_operation == arr_op && single_operation == single_op &&  \
        set_b == set_b_v) {                                            \
        printf("Executing %d, %d, %d\n", arr_op, single_op, set_b);    \
        array_calculation_##arr_op##_##single_op##_##set_b_v(a, b, n); \
    }

    CALL(ADD, ADD_SUB, true)
    CALL(ADD, ADD_SUB, false)
    CALL(ADD, MUL_DIV, true)
    CALL(ADD, MUL_DIV, false)
    CALL(ADD, SIN_COS, true)
    CALL(ADD, SIN_COS, false)
    CALL(ADD, SQRT_ABS, true)
    CALL(ADD, SQRT_ABS, false)
    CALL(SUBTRACT, ADD_SUB, true)
    CALL(SUBTRACT, ADD_SUB, false)
    CALL(SUBTRACT, MUL_DIV, true)
    CALL(SUBTRACT, MUL_DIV, false)
    CALL(SUBTRACT, SIN_COS, true)
    CALL(SUBTRACT, SIN_COS, false)
    CALL(SUBTRACT, SQRT_ABS, true)
    CALL(SUBTRACT, SQRT_ABS, false)
    CALL(REPLACE, ADD_SUB, true)
    CALL(REPLACE, ADD_SUB, false)
    CALL(REPLACE, MUL_DIV, true)
    CALL(REPLACE, MUL_DIV, false)
    CALL(REPLACE, SIN_COS, true)
    CALL(REPLACE, SIN_COS, false)
    CALL(REPLACE, SQRT_ABS, true)
    CALL(REPLACE, SQRT_ABS, false)
}
