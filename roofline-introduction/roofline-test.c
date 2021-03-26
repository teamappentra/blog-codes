#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void fill_array(float a[], int N) {
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
}

float calculate_sum(float a[], int N) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }
    return sum;
}

void calculate_distance(float x[], float y[], int N, float distance[]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float x_dist = x[i] - x[j];
            float y_dist = y[i] - y[j];
            distance[j + i * N] = sqrt(x_dist * x_dist + y_dist * y_dist);
        }
    }
}

#define ARR_LEN (100 * 1024 * 1024)

float x[ARR_LEN];
float y[ARR_LEN];
float r[ARR_LEN];

int main(int argc, char* argv[]) {
    float sum;
    int new_len = (int)sqrtl(ARR_LEN);

    fill_array(x, ARR_LEN);
    fill_array(y, ARR_LEN);

    sum = calculate_sum(x, ARR_LEN);
    printf("sum = %f\n", sum);

    calculate_distance(x, y, new_len, r);
    printf("distance[5][10] = %f\n", r[5 * new_len + 10]);
}
