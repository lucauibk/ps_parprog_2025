//D(m, n) = 1                          if m = 0 or n = 0
//D(m-1, n) + D(m-1, n-1) + D(m, n-1)   otherwise

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

unsigned long long delannoy(int m, int n) {
    if(m == 0 || n == 0){
        return 1;
    }else{
        return delannoy(m-1, n) + delannoy(m-1, n-1) + delannoy(m, n-1);
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    double start = omp_get_wtime();
    unsigned long long result = delannoy(N, N);
    double end = omp_get_wtime();

    printf("Delannoy(%d, %d) = %llu\n", N, N, result);
    printf("Time: %.6f seconds\n", end - start);
    return 0;
}
