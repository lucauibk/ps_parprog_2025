# Assignment 10

The goal of this assignment is to practice using OpenMP affinity and tasks.

## Exercise 1 (1.5 Points)

### Description

This exercise consists of exploring the effects of OpenMP thread affinity.

### Tasks

1) Write an OpenMP program that atomically increments an `int` using `#pragma omp atomic` in a parallel for loop for a large number of iterations, i.e. such that the program takes at least 2 seconds to execute. Have the program print the time required to process the entire loop. Compile your program with gcc 12.2.0 and optimization level `-O3`. Do not perform any manual optimizations such as reducing the number of atomic operations.
2) Run your program with 6 threads. Explore the affinity features of OpenMP 4.0 to change the way threads are mapped to cores, e.g. using a single CPU only or using both CPUs. Explain the affinity settings that you chose.
3) Benchmark your program with these affinity settings. What can you observe?
4) Enter the time for N=500.000.000 into the comparison spreadsheet linked on Discord.

## Exercise 2 (1.5 Points)

### Description

This exercise consists of implementing a program that calculates Delannoy numbers with OpenMP tasks.

A Delannoy number specifies the number of paths from the south-west corner of a 2D grid to the north-east corner, using only the per-step directions north, north-east, and east. See https://en.wikipedia.org/wiki/Delannoy_number for more information and a visualization.

### Tasks

- Implement a sequential program that computes the Delannoy number for a square 2D grid of size NxN where N is an input parameter for your program. If in doubt, base your implementation on the formula given in the Wikipedia article under "basic recurrence relation". Make sure your program is semantically correct by comparing the result against the Delannoy numbers given in the article.
- Parallelize your program using OpenMP tasks and benchmark both the sequential and parallel implementation for several N between 3 and ~15. What can you observe?
- What is the main bottleneck of your parallel implementation and how can it be improved without changing the underlying algorithm?
- Enter the wall clock time of the sequential version and the parallel version for 1 and 12 threads for N=12 on LCC3 to the comparison spreadsheet linked on Discord.

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
