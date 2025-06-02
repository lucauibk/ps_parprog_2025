CC = gcc
CFLAGS = -O1 -fopenmp-simd

simd: vec_parallel.c
	$(CC) $(CFLAGS) -o simd vec_parallel.c

clean:
	rm -f simd
