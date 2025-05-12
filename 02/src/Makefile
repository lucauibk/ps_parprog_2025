CC = gcc
CFLAGS = -fopenmp -O2
THREADS = 1 2 4 8 12
RUNS = 5  # Anzahl der Wiederholungen für Stabilitätstests
OUTPUT = results.txt
STABILITY_OUTPUT = stability_results.txt

all: compile run stability

compile:
	$(CC) $(CFLAGS) -o slow slow.c
	$(CC) $(CFLAGS) -o medium medium.c
	$(CC) $(CFLAGS) -o fast fast.c

run:
	@echo "Running tests..." >> $(OUTPUT)
	@for prog in slow medium fast; do \
	    for t in $(THREADS); do \
	        echo "Running $$prog with $$t threads:" >> $(OUTPUT); \
	        OMP_NUM_THREADS=$$t ./$$prog >> $(OUTPUT); \
	        echo "-----------------------------------" >> $(OUTPUT); \
	    done; \
	done;

stability:
	@echo "Running stability tests...\n" >> $(STABILITY_OUTPUT)
	@for prog in slow medium fast; do \
	    echo "Stability test for $$prog with 8 threads:" >> $(STABILITY_OUTPUT); \
	    for run in $(shell seq 1 $(RUNS)); do \
	        echo "Run $$run:" >> $(STABILITY_OUTPUT); \
	        OMP_NUM_THREADS=8 ./$$prog >> $(STABILITY_OUTPUT); \
	    done; \
	    echo "-----------------------------------" >> $(STABILITY_OUTPUT); \
	done;

clean:
	rm -f slow medium fast $(OUTPUT) $(STABILITY_OUTPUT)