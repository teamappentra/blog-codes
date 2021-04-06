#include <errno.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void show_fe_exceptions(void) {
    printf("current exceptions raised: ");
    if (fetestexcept(FE_DIVBYZERO))
        printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT))
        printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID))
        printf(" FE_INVALID");
    if (fetestexcept(FE_OVERFLOW))
        printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW))
        printf(" FE_UNDERFLOW");
    if (fetestexcept(FE_ALL_EXCEPT) == 0)
        printf(" none");
    printf(", errno = %s\n", strerror(errno));
}

void clear_exceptions(void) {
    errno = 0;
    feclearexcept(FE_ALL_EXCEPT);
}

void fenv_demo(float a) {
    clear_exceptions();

    printf("%f, 5 / a = %f\n", a, 5 / a);
    show_fe_exceptions();
    clear_exceptions();

    printf("sqrt(%f) = %f\n", a, sqrtf(a));
    show_fe_exceptions();
    clear_exceptions();

    return;
}

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
