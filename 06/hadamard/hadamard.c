#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int hadamard_product_1(){
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    #pragma omp parallel for shedule(static)
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    return c;
    
}

int hadamard_product_2(){
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    #pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c[i][j] = a[i][j] * b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return c;

}

int hadamard_product_3(){
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    #pragma omp parallel for schedule(guided)
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c[i][j] = a[i][j] * b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return c;

}

int hadamard_product_4(){
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    #pragma omp parallel for schedule(auto)
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c[i][j] = a[i][j] * b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return c;

}

int main(){
    printf("Hadamard product 1\n");
    double start = omp_get_wtime();
    printf("%d/n", hadamard_product_1());
    double end1 = omp_get_wtime();
    printf("Hadamard product 1 time: %f\n", (start - end1)); 
    printf("%d/n", hadamard_product_2());
    double end2 = omp_get_wtime();
    printf("Hadamard product 2 time: %f\n", (end1 - end2));
}