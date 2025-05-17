#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	//iterate over each pixel
    #pragma omp parallel for collapse(2) schedule(dynamic)
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
}


int main() {
	uint8_t image[Y][X];

	double start = omp_get_wtime(); // Startzeit
    calc_mandelbrot(image);
    double end = omp_get_wtime();   // Endzeit

    printf("Time: %.4f seconds\n", end - start);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}