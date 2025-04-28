#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long n = 700000000;
    long i, count = 0;
    double x, y, pi;
    double startTime, endTime;
    
    startTime = omp_get_wtime();
    
    #pragma omp parallel private(x, y)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < n; i++) {
            x = (double) rand_r(&seed) / RAND_MAX;
            y = (double) rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1) {
                #pragma omp atomic
                count++;
            }
        }
    }

    endTime = omp_get_wtime();

    pi = 4.0 * count / n;
    printf("[Atomic] Approximate value of pi: %f\n", pi);
    printf("Time: %2.4f seconds\n", endTime - startTime);
    
    return 0;
}
