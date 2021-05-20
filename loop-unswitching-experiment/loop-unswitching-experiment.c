
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "calculation-default.h"
#include "calculation-unswitched.h"
#include "utils.h"

enum single_operation_e single_operation;
enum array_operation_e array_operation;

#define ARR_LEN (256 * 1024 * 1024)

int main(int argc, char* argv[]) {
    bool set_b;

    if (argc < 4) {
        printf(
            "Missing parameters: array operation [0-2], single operation "
            "[0-3], set b [0-1]\n");
        return -1;
    }

    array_operation = atoi(argv[1]);
    single_operation = atoi(argv[2]);
    set_b = atoi(argv[3]);

    printf("Compiler: %s\n", get_compiler_string());
    printf("array size = %d\n", ARR_LEN);
    printf("array operation = %s\n",
           array_operation_to_string(array_operation));
    printf("single operation = %s\n",
           single_operation_to_string(single_operation));
    printf("set_b = %s\n", set_b ? "true" : "false");

    float* arr1 = malloc(ARR_LEN * sizeof(float));
    float* arr2 = malloc(ARR_LEN * sizeof(float));
    float* arr3 = malloc(ARR_LEN * sizeof(float));
    float* arr4 = malloc(ARR_LEN * sizeof(float));

    fill_array(arr1, ARR_LEN);
    fill_array(arr2, ARR_LEN);

    memcpy(arr3, arr1, sizeof(float) * ARR_LEN);
    memcpy(arr4, arr2, sizeof(float) * ARR_LEN);

    printf("Default loop unswitching\n");

    double default_time_spent, forced_time_spent;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    array_calculation(arr1, arr2, ARR_LEN, set_b);

    default_time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__,
           arr1[0] + arr2[ARR_LEN - 1], default_time_spent);

    printf("Manual unswitch everything\n");

    clock_gettime(CLOCK_MONOTONIC, &start);

    array_calculation_unswitched(arr3, arr4, ARR_LEN, set_b);

    forced_time_spent = get_runtime(start);
    printf("%s: Result = %f, runtime = %f\n", __FUNCTION__,
           arr1[0] + arr2[ARR_LEN - 1], forced_time_spent);

    printf("in_array1 different count = %d, in_arra2 different count = %d\n",
           compare_arrays(arr1, arr3, ARR_LEN),
           compare_arrays(arr2, arr4, ARR_LEN));

    printf("XLS|%s|%s|%s|%s|%f|%f\n",
           array_operation_to_string(array_operation),
           single_operation_to_string(single_operation), bool_to_string(set_b),
           get_compiler_string(), default_time_spent, forced_time_spent);

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);

    return 0;
}
