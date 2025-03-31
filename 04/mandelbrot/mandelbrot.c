#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000
#define NUM_THREADS 4

uint8_t image[Y][X];

typedef struct {
    int start_row;
    int end_row;
} Thread_Data;

void* calc_mandelbrot_thread(void* arg) {
	Thread_Data* data = (Thread_Data*)arg; // Cast the argument to the correct type

    for (int py = 0; py < Y; py++) {
        for (int px = 0; px < X; px++) {
            double x = 0.0, y = 0.0;
            double cx = ((double)px / X) * 3.5 - 2.5; // Scale and translate x to [-2.5, 1]
            double cy = ((double)py / Y) * 2.0 - 1.0; // Scale and translate y to [-1, 1]
            int iteration = 0;
            // Iterate the Mandelbrot function z = z^2 + c
			// until the magnitude of z exceeds 2 or the maximum number of iterations is reached
            while ((x * x + y * y <= 4.0) && (iteration < MAX_ITER)) {
                double x_tmp = x * x - y * y + cx;
                y = 2 * x * y + cy;
                x = x_tmp;
                iteration++;
            }
            
            // Normalize iteration count to range [0, 255]
            image[py][px] = (uint8_t)(255 * ((double)iteration / MAX_ITER));
        }
    }
    return NULL;
}

void calc_mandelbrot_parallel(int num_threads){
    pthread_t threads[num_threads]; // Array to store the thread IDs
    Thread_Data thread_data[num_threads]; // Array to store the data for each thread

    int rows_per_thread = Y / num_threads; // split the rows between the threads
    for(int i = 0; i < num_threads; i++){
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? Y : (i + 1) * rows_per_thread; // last thread takes the remaining rows
        pthread_create(&threads[i], NULL, calc_mandelbrot_thread, &thread_data[i]); // Create the thread thread_data[i] is the argument passed to the thread
    } 
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

}


int main() {
	int num_threads = NUM_THREADS;

	calc_mandelbrot_parallel(num_threads);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}