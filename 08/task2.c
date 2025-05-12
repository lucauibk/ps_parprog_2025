#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int N = 100;
    int A[1000];
    int Anew[1000];
        for (int i=4; i<=N; i+=9) {
            for (int j=0; j<=N; j+=5) {
                A[i] = 0;
            }
            printf("old: %d\n", i);
        }

    //Li = 4 , Si = 9 , Lj = 0 , Sj = 5
    for(int inew=0; inew <= (N-4)/9; inew++){
        for(int jnew = 0; jnew <= N/5; jnew++){
            Anew[9 * inew + 4] = 0;
        }
        printf("new: %d\n", 9 * inew + 4);
    }
}