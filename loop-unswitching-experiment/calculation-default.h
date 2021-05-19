#pragma once

#include <math.h>
#include "utils.h"

extern enum single_operation_e single_operation;
extern enum array_operation_e array_operation;

void single_calculation(int in1, int in2, float* out1, float* out2) {
    switch (single_operation) {
        case ADD_SUB:
            *out1 = in1 + in2;
            if (out2) {
                *out2 = in1 - in2;
            }
            break;
        case MUL_DIV:
            *out1 = in1 * in2;
            if (out2) {
                *out2 = in1 / (in2 + (in2 == 0));
            }
            break;
        case SIN_COS:
            *out1 = sinf(in1);
            if (out2) {
                *out2 = cosf(in1);
            }
            break;
        case SQRT_ABS:
            *out1 = abs(in1);
            if (out2) {
                *out2 = sqrt(abs(in2));
            }
            break;
    }
}

void array_calculation(float* a, float* b, int n, bool set_b) {
    float r1, r2;
    for (int i = 0; i < n; i++) {
        single_calculation(i, i + 1, &r1, &r2);
        if (array_operation == ADD) {
            a[i] += r1;
            if (set_b) {
                b[i] += r2;
            }
        } else if (array_operation == SUBTRACT) {
            a[i] -= r1;
            if (set_b) {
                b[i] -= r2;
            }
        } else {
            a[i] = r1;
            if (set_b) {
                b[i] = r2;
            }
        }
    }
}