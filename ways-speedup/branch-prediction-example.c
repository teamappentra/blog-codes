#include <stdio.h>
#include <string.h>
#include "utils.h"

void calculate_hysteresis(int cond[], int in[], int n, int out[]) {
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 0; i < n; i++) {
        if (cond[i] > 0) {
            out[in[i]]++;
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, out[0] + out[1],
           time_spent);
}

void calculate_hysteresis_branchless(int cond[], int in[], int n, int out[]) {
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 0; i < n; i++) {
        out[in[i]] += (cond[i] > 0);
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, out[0] + out[1],
           time_spent);
}

#define ARR_LEN (100 * 1024 * 1024)
#define HIST_LEN (32768)

int in_arr[ARR_LEN];
int out_arr[ARR_LEN];

int hist_arr[HIST_LEN];
int hist_arr2[HIST_LEN];

int main(int argc, char** argv) {
    fill_array(in_arr, ARR_LEN);

    fill_histogram_array(out_arr, ARR_LEN,
                         sizeof(hist_arr) / sizeof(hist_arr[0]));

    printf("The element of in[i] have 50%% chance of being positive\n");
    memset(hist_arr, 0, sizeof(hist_arr));
    calculate_hysteresis(in_arr, out_arr, ARR_LEN, hist_arr);

    memset(hist_arr2, 0, sizeof(hist_arr2));
    calculate_hysteresis_branchless(in_arr, out_arr, ARR_LEN, hist_arr2);

    return 0;
}