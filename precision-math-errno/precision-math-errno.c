#include <errno.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


double rolling_average(double a[], int n) {
    int i;
    double result = 0.0;

    for (i = 0; i < n; i++) {
        result += sqrt(a[i]) / n;
    }

    return result;
}

void fill_array(double a[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        a[i] = (double)rand();
    }
}

#define ARR_LEN (100 * 1024 * 1024)
double my_array[ARR_LEN];

int main(int argc, char** argv) {
    fill_array(my_array, ARR_LEN);

    clock_t begin = clock();
    double avg = rolling_average(my_array, ARR_LEN);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Average = %.17g, runtime = %f, errno = %d \n", avg, time_spent, errno);

    return 0;
}
