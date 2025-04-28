#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long n = 700000000;
    long count = 0;
    double x, y, pi;
    double startTime, endTime;
    
    startTime = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:count) private(x, y)
    for (long i = 0; i < n; i++) {
        unsigned int seed = omp_get_thread_num() * n + i; // Bessere Verteilung des Seeds

        x = (double) rand_r(&seed) / RAND_MAX;
        y = (double) rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1) {
            count++;
        }
    }

    endTime = omp_get_wtime();

    pi = 4.0 * count / n;
    printf("[Reduction] Approximate value of pi: %f\n", pi);
    printf("Time: %2.4f seconds\n", endTime - startTime);
    
    return 0;
}
