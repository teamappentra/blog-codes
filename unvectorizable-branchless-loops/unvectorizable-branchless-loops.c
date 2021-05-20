#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill_array(int a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (int)rand();
        if (a[i] % 2 == 0) {
            a[i] = -a[i];
        }
    }
}

void normalize_array_to_80_percent_positive(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int val = rand() % 5;
        if (val == 0) {
            a[i] = -abs(a[i]);
        } else {
            a[i] = abs(a[i]);
        }
    }
}

void fill_histogram_array(int a[], int n, int max) {
    for (int i = 0; i < n; i++) {
        a[i] = (int)rand() % max;
    }
}

void calculate_hysteresis_naive(int cond[], int in[], int n, int out[]) {
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

int condition_data_cache_naive(int in[], int n, int out[]) {
    int count = 0;
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 1; i < n; i++) {
        if (out[in[i]] > 0) {
            count = (count + 1) % 1000;
        }
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, count, time_spent);

    return count;
}

int condition_data_cache_branchless(int in[], int n, int out[]) {
    int count = 0;
    clock_t begin = clock(), end;
    double time_spent;

    for (int i = 1; i < n; i++) {
        count = (count + (out[in[i]] > 0)) % 1000;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, count, time_spent);

    return count;
}

#define CONDITIONAL_COPY_NAIVE(name, COMP)                          \
    int conditional_copy_naive_##name(int in[], int n, int out[]) { \
        int j = 0;                                                  \
        clock_t begin, end;                                         \
        double time_spent;                                          \
        begin = clock();                                            \
        for (int i = 0; i < n; i++) {                               \
            if (in[i] < 0) {                                        \
                out[j] = COMP(in[i]);                               \
                j++;                                                \
            }                                                       \
        }                                                           \
        end = clock();                                              \
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;        \
        printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, j,  \
               time_spent);                                         \
        return j;                                                   \
    }

#define CONDITIONAL_COPY_BRANCHLESS(name, COMP)                          \
    int conditional_copy_branchless_##name(int in[], int n, int out[]) { \
        int j = 0;                                                       \
        clock_t begin, end;                                              \
        double time_spent;                                               \
        begin = clock();                                                 \
        for (int i = 0; i < n; i++) {                                    \
            out[j] = COMP(in[i]);                                        \
            j += (in[i] < 0);                                            \
        }                                                                \
        end = clock();                                                   \
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;             \
        printf("%s: Result = %d, runtime = %f\n", __FUNCTION__, j,       \
               time_spent);                                              \
        return j;                                                        \
    }

#define MOVE(x) (x)
#define SQRT(x) ((int)sqrtf((float)abs(x)))
#define SIN(x) ((int)sinf((float)x))

CONDITIONAL_COPY_NAIVE(move, MOVE)
CONDITIONAL_COPY_NAIVE(sqrt, SQRT)
CONDITIONAL_COPY_NAIVE(sin, SIN)

CONDITIONAL_COPY_BRANCHLESS(move, MOVE)
CONDITIONAL_COPY_BRANCHLESS(sqrt, SQRT)
CONDITIONAL_COPY_BRANCHLESS(sin, SIN)

#define ARR_LEN (100 * 1024 * 1024)
#define HIST_LEN (32768)

int in_arr[ARR_LEN];
int out_arr[ARR_LEN];

int hist_arr[HIST_LEN];
int hist_arr2[HIST_LEN];

#define SMALL_HIST_LEN 256
#define LARGE_HIST_LEN (8 * 1024 * 1024)

int main(int argc, char** argv) {
    fill_array(in_arr, ARR_LEN);

    conditional_copy_naive_move(in_arr, ARR_LEN, out_arr);
    conditional_copy_naive_sqrt(in_arr, ARR_LEN, out_arr);
    conditional_copy_naive_sin(in_arr, ARR_LEN, out_arr);

    conditional_copy_branchless_move(in_arr, ARR_LEN, out_arr);
    conditional_copy_branchless_sqrt(in_arr, ARR_LEN, out_arr);
    conditional_copy_branchless_sin(in_arr, ARR_LEN, out_arr);

    fill_histogram_array(out_arr, ARR_LEN,
                         sizeof(hist_arr) / sizeof(hist_arr[0]));

    printf("The element of in[i] have 50%% chance of being positive\n");
    memset(hist_arr, 0, sizeof(hist_arr));
    calculate_hysteresis_naive(in_arr, out_arr, ARR_LEN, hist_arr);

    memset(hist_arr2, 0, sizeof(hist_arr2));
    calculate_hysteresis_branchless(in_arr, out_arr, ARR_LEN, hist_arr2);

    normalize_array_to_80_percent_positive(in_arr, ARR_LEN);
    printf("The element of in[i] have 80%% chance of being positive\n");
    memset(hist_arr, 0, sizeof(hist_arr));
    calculate_hysteresis_naive(in_arr, out_arr, ARR_LEN, hist_arr);

    memset(hist_arr2, 0, sizeof(hist_arr2));
    calculate_hysteresis_branchless(in_arr, out_arr, ARR_LEN, hist_arr2);

    fill_array(out_arr, ARR_LEN);
    fill_histogram_array(in_arr, ARR_LEN, SMALL_HIST_LEN);

    condition_data_cache_naive(in_arr, ARR_LEN, out_arr);
    condition_data_cache_branchless(in_arr, ARR_LEN, out_arr);

    fill_histogram_array(in_arr, ARR_LEN, LARGE_HIST_LEN);
    condition_data_cache_naive(in_arr, ARR_LEN, out_arr);
    condition_data_cache_branchless(in_arr, ARR_LEN, out_arr);

    return 0;
}