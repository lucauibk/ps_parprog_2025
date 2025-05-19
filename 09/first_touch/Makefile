CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3

.PHONY: all
all: first_touch
ex1: first_touch.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) first_touch