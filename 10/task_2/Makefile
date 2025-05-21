CC = gcc
CFLAGS = -O3 -pthread -std=gnu11 -Wall -Wextra -lm

.PHONY: all clean
all: delannoy_par delannoy_seq

delannoy_par: delannoy_par.o
	$(CC) $(CFLAGS) -o $@ $<
delannoy_seq: delannoy_seq.o
	$(CC) $(CFLAGS) -o $@ $<
delannoy_par.o: delannoy_par.c
	$(CC) $(CFLAGS) -c $<
delannoy_seq.o: delannoy_seq.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f delannoy_par delannoy_seq *.o