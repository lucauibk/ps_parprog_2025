CFLAGS = -O3 -pthread -std=gnu11 -Wall -Wextra -lm

.PHONY: all
all: mandelbrot

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot.png *.log

mandelbrot: mandelbrot.c
	$(CC) $(CFLAGS) -o $@ $^
