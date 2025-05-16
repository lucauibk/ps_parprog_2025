FLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3

.PHONY: all
all: ex1 ex1_fixed
ex1: ex1.c
	$(CC) $(CFLAGS) -o $@ $<
ex1_fixed: ex1_fixed.c
	$(CC) $(CFLAGS) -o $@ $<
.PHONY: clean
clean:
	$(RM) ex1 ex1_fixed