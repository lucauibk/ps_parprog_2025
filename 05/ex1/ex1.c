#include <omp.h>
#include <stdio.h>
//flush schreibt von cache in den Speicher
//atomic stellt sicher das nur ein Thread auf die Variable zugreift

int main() {

    int data;
    int flag = 0;

    #pragma omp parallel num_threads(2)
    {

      if (omp_get_thread_num() == 0) {

          data = 42;

          flag = 1;
          
          #pragma omp flush(data, flag) // Synchronisiert flag und data zwischen den Threads

      } else if(omp_get_thread_num() == 1) {
        
          int flag_val = 0;

          while (flag_val < 1) {
             #pragma omp flush(flag) // Stellt sicher, dass Thread 1 den aktuellen Wert von flag liest
             flag_val = flag;

          }
          #pragma omp flush(data) // Stellt sicher, dass data korrekt gelesen wird
          printf("flag=%d data=%d\n", flag, data);

      }

    }
    
    return 0;
}
