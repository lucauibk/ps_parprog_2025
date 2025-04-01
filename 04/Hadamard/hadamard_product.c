#include <stdio.h>
#include <stdlib.h>

int hadamard_product_1(){
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
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
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c[i][j] = a[i][j] * b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return c;
    
}

int main(int argc, char* argv[]){
    printf("Hadamard product 1\n");
    printf("%d/n", hadamard_product_1());
    printf("Hadamard product 2\n");
    printf("%d/n", hadamard_product_2());
}