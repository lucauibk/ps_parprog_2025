# Assignment 9

The goal of this assignment is to expand your knowledge on and familiarity with OpenMP.

## Exercise 1 (1.5 Points)

### Description

This exercise deals with performance analysis and improvement of a given code [ex1/ex1.c](ex1/ex1.c). The program reads a matrix size n from the command-line. Then two square matrices a and b of size n\*n are filled with random numbers. Finally, the program should print the sum of all elements of matrix c and the wall clock time after the matrix multiplication c=a\*b was conducted.

### Tasks

1) Are there any functional or issues in the given code? Document your findings.
2) Improve the performance of the given source code, fix any functional bugs you find.
3) Benchmark your modification of the code and the original implementation with 1, 2, 4, 6, and 12 threads on LCC3 using n=1,500. Has your effort paid off?
4) Enter your shortest wall clock time for 12 threads and n=1,500 on LCC3 to the comparison spreadsheet linked on Discord.

## Exercise 2 (1.5 Points)

### Description

In this exercise, you are asked to investigate the effect of first touch in multi-threaded programs, as discussed in lecture part 3-1 OpenMP.

### Tasks

1) Open [first_touch/first_touch.c](first_touch/first_touch.c), familiarize yourself with the code and parallelize it using OpenMP. Be sure to fix both the number of threads and affinity using `OMP_NUM_THREADS=12`and `GOMP_CPU_AFFINITY=0-11`.
2) How can you demonstrate the effect of first touch on your OpenMP implementation with minimal code changes? Illustrate the performance for both cases, i.e. when benefiting from the effect of first touch and when not benefiting from it.
3) Do loop scheduling strategies affect first touch? If yes, why? If not, why not?
4) Enter the wall clock time for both cases of 2) for 12 threads and n=40,000 on LCC3 to the comparison spreadsheet linked on Discord.
