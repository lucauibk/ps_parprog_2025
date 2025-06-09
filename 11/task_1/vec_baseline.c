#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize(float* a, float* b, float* c, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = 1.0f;
        b[i] = 2.0f;
        c[i] = 3.0f;
    }
}

void compute(float* a, float* b, float* c, int size, int repetitions) {
    for (int run = 0; run < repetitions; ++run) {
        for (int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}

float verify(float* a, int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; ++i)
        sum += a[i];
    return sum;
}

int main(int argc, char** argv) {
    int size = (argc > 1) ? atoi(argv[1]) : 2048;
    int repetitions = (argc > 2) ? atoi(argv[2]) : 1000000;


    float* a = aligned_alloc(64, size * sizeof(float));
    float* b = aligned_alloc(64, size * sizeof(float));
    float* c = aligned_alloc(64, size * sizeof(float));

    initialize(a, b, c, size);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    compute(a, b, c, size, repetitions);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Elapsed time: %.4f seconds\n", elapsed);
    printf("Verification: sum(a) = %f\n", verify(a, size));

    free(a);
    free(b);
    free(c);

    return 0;
}
