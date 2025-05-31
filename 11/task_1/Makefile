CC = gcc
CFLAGS_BASELINE = -O1
CFLAGS_VEC = -O1 -ftree-vectorize
SRC = vec_baseline.c

.PHONY: all clean

all: vec_baseline auto_vectorized

vec_baseline: $(SRC)
	$(CC) $(CFLAGS_BASELINE) -o $@ $<

auto_vectorized: $(SRC)
	$(CC) $(CFLAGS_VEC) -o $@ $<

clean:
	rm -f vec_baseline auto_vectorized
