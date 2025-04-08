# Assignment 6

The goal of this assignment is to expand your knowledge on and familiarity with OpenMP.

## Exercise 1 (1 Point)

### Description

There are several methods to approximate Pi numerically. In this exercise, you are asked to approximate Pi using the Monte Carlo method. Therefore, n (n >> 1) random 2D points equally distributed in the interval [0, 1] x [0, 1] are generated, and it is checked whether they are inside the first quadrant of a unit circle. Let i be the number of points that lie inside the quarter of the unit circle. Then Pi can be approximated by 4 * i / n. 
The code can be found in the provided serial implementation.

### Tasks

1) Implement three parallel versions of Monte Carlo Pi approximation using OpenMP and the provided serial implementation [ex1/serial.c](ex1/serial.c) with the constructs:
   1) ```critical``` section
   2) ```atomic``` statement
   3) ```reduction``` clause
2) To further increase any performance effects between them, increment the samples counter directly without aggregating into private variables first.
3) Benchmark your parallel implementations with 1, 4, 8 and 12 threads on LCC3 using n=700000000 using OpenMP's time measurement function. What can you observe?
4) Add the time of 12 threads to the comparision spreadsheet.

## Exercise 2 (1 Point)

### Description

In Assignment 2 and 3 you were asked to implement a program that calculates the [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) in serial and parallel using `Posix Threads`.
In this exercise you will finally see the benefit of using `OpenMP`.

### Tasks

1) Implement the Mandelbrot set calculation in OpenMP.
2) Benchmark your implementation with 1, 4, 8 and 12 threads and describe your observations.
3) Add the time of 12 threads to the comparision spreadsheet.

## Exercise 3 (1 Point)

### Description

This exercise consists of extending the Hadamard product implementation of assignment 4.

### Tasks

1) Implement a parallel version of the Hadamard product using OpenMP. Use the snippet below as sequential implementation.

    ```c
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    ```

2) Use the loop scheduling methods discussed in the lecture, `static`, `dynamic`, `guided` and `auto`. Explain their differences and compare their performance for both the Hadamard and Mandelbrot OpenMP implementations. What can you observe?
3) In addition, try the loop scheduling methods `auto` and `runtime`. What do they do, what can you observe?
4) Benchmark your  parallel implementations with 1, 4, 8 and 12 threads on LCC3 using N=10.000², 20.000² and 30.000². Use OpenMP's time measurement function to measure only the computational loop.
5) Enter the time for N=32.768² into the comparison spreadsheet.
