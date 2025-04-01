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

uint8_t image[Y][X];  // Gemeinsames Bild-Array

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

void* calc_mandelbrot_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int py = data->start_row; py < data->end_row; py++) {
        for (int px = 0; px < X; px++) {
            double x = 0.0, y = 0.0;
            double cx = ((double)px / X) * 3.5 - 2.5;
            double cy = ((double)py / Y) * 2.0 - 1.0;
            int iteration = 0;
            while ((x * x + y * y <= 4.0) && (iteration < MAX_ITER)) {
                double x_tmp = x * x - y * y + cx;
                y = 2 * x * y + cy;
                x = x_tmp;
                iteration++;
            }
            image[py][px] = (uint8_t)(255 * ((double)iteration / MAX_ITER));
        }
    }
    return NULL;
}

void calc_mandelbrot_parallel(int num_threads) {
    pthread_t threads[num_threads]; //
    ThreadData thread_data[num_threads];

    int rows_per_thread = Y / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? Y : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, calc_mandelbrot_thread, &thread_data[i]); // startet thread und führt calc_mandelbrot_thread aus
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num_threads = atoi(argv[1]);
    calc_mandelbrot_parallel(num_threads);

    // Bild speichern
    const int channel_nr = 1, stride_bytes = 0;
    stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
    
    return EXIT_SUCCESS;
}