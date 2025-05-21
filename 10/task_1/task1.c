#include <stdio.h>
#include <omp.h>

int main() {
    const long N = 500000000; // 500 Mio
    int counter = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; ++i) {
        #pragma omp atomic
        counter++;
    }

    double end_time = omp_get_wtime();

    printf("Final counter value: %d\n", counter);
    printf("Time taken: %.3f seconds\n", end_time - start_time);

    return 0;
}
