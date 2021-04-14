
#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"


double calculate(double in) {
#ifdef LOW_INTENSITY
    return fabs(in);
#else
    return cos(sqrt(fabs(in)));
#endif
}

void fill_array(double a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (double)rand() - 1000000.0;
    }
}

double break_loop_naive(double in[], int n, double flag) {
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        if (in[i] == flag) {
            break;
        }

        sum += calculate(in[i]);
    }

    return sum;
}

double break_loop_split(double in[], int n, double flag) {
    double sum = 0.0;
    int m;

    for (m = 0; m < n; m++) {
        if (in[m] == flag) {
            break;
        }
    }

    for (int i = 0; i < m; i++) {
        sum += calculate(in[i]);
    }

    return sum;
}

struct result {
    double sum;
    int max_index;
};

struct result search_loop_naive(double in[], int n) {
    int index = -1;
    double max = 0.0;
    double sum = 0.0;
    struct result r;

    for (int i = 0; i < n; i++) {
        double r = calculate(in[i]);

        if (r > max) {
            max = r;
            index = i;
        }

        sum += r;
    }

    r.sum = sum;
    r.max_index = index;
    return r;
}

struct result search_loop_split(double in[], int n) {
    int index = -1;
    double max = 0.0;
    double sum = 0.0;
    struct result r;

    double* tmp = malloc(sizeof(double) * n);

    for (int i = 0; i < n; i++) {
        double r = calculate(in[i]);
        tmp[i] = r;
        sum += r;
    }


    for (int i = 0; i < n; i++) {
        if (tmp[i] > max) {
            max = tmp[i];
            index = i;
        }
    }

    free(tmp);

    r.sum = sum;
    r.max_index = index;
    return r;
}


double sum(double in[], int n) {
    double r = 0.0;
    for (int i = 0; i < n; i++) {
        r+=in[i];
    }
    return r;
}

#define ARR_LEN (100 * 1024 * 1024)
double my_array[ARR_LEN];
double out_array[ARR_LEN];

int main(int argc, char** argv) {
    clock_t begin, end;
    double res, time_spent;
    struct result r;
    
    fill_array(my_array, ARR_LEN);

    begin = clock();
    res = break_loop_naive(my_array, ARR_LEN, my_array[ARR_LEN - 1]);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("BREAK LOOP NAIVE: Result = %.17g, runtime = %f\n", res, time_spent);

    begin = clock();
    res = break_loop_split(my_array, ARR_LEN, my_array[ARR_LEN - 1]);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("BREAK LOOP SPLIT: Result = %.17g, runtime = %f\n", res, time_spent);



    begin = clock();
    r = search_loop_naive(my_array, ARR_LEN);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("SEARCH LOOP NAIVE: Result = %.17g, max_index = %d , runtime = %f\n", r.sum, r.max_index, time_spent);

    begin = clock();
    r = search_loop_split(my_array, ARR_LEN);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("SEARCH LOOP SPLIT: Result = %.17g, max_index = %d , runtime = %f\n", r.sum, r.max_index, time_spent);


    return 0;
}