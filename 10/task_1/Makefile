# Makefile for OpenMP atomic counter program

CC = gcc
CFLAGS = -O3 -fopenmp
TARGET = task1
SRC = task1.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
