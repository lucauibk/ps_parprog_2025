# Makefile for OpenMP atomic counter program

CC = gcc
CFLAGS = -O3 -fopenmp
TARGET = atomic_counter
SRC = atomic_counter.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
