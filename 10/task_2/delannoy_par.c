//D(m, n) = 1                           if m = 0 or n = 0
//D(m-1, n) + D(m-1, n-1) + D(m, n-1)   otherwise
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

unsigned long long delannoy(int m, int n) {
    if(m == 0 || n == 0){
        return 1;
    }else{
        // Parallelize the recursive calls using OpenMP
        unsigned long long result1, result2, result3;
        #pragma omp task shared(result1)
        {
            result1 = delannoy(m-1, n);
        }
        #pragma omp task shared(result2)
        {
            result2 = delannoy(m-1, n-1);
        }
        #pragma omp task shared(result3)
        {
            result3 = delannoy(m, n-1);
        }
        #pragma omp taskwait // Wait for all tasks to finish
        // Combine the results from the parallel tasks
        return result1 + result2 + result3;
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    long long result;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = delannoy(N, N);
        }
    }
    double end = omp_get_wtime();

    printf("Delannoy(%d, %d) = %llu\n", N, N, result);
    printf("Time: %.6f seconds\n", end - start);
    return 0;
}
