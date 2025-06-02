#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize(double* a, double* b, double* c, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = 1.0f;
        b[i] = 2.0f;
        c[i] = 3.0f;
    }
}

void compute(double* a, double* b, double* c, int size, int repetitions) {
    for (int run = 0; run < repetitions; ++run) {
        #pragma omp simd
        for (int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}


double verify(double* a, int size) {
    double sum = 0.0f;
    for (int i = 0; i < size; ++i)
        sum += a[i];
    return sum;
}

int main(int argc, char** argv) {
    int size = (argc > 1) ? atoi(argv[1]) : 2048;
    int repetitions = (argc > 2) ? atoi(argv[2]) : 1000000;

    double* a = aligned_alloc(64, size * sizeof(double));
    double* b = aligned_alloc(64, size * sizeof(double));
    double* c = aligned_alloc(64, size * sizeof(double));

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
