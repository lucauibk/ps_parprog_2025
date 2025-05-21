#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do { \
		PERROR; \
		goto label; \
	} while (0)

#define INIT_ARRAY(arr, label) \
	do { \
		for (long i = 0; i < n; ++i) { \
			(arr)[i] = calloc(n, sizeof(**(arr))); /* FIXED: calloc ensures zero-initialized matrix */ \
			if (!(arr)[i]) PERROR_GOTO(label); \
		} \
	} while (0)

void free_2d_array(int **arr, long len) {
	if (!arr) {
		return;
	}
	for (long i = 0; i < len; ++i) {
		if (!arr[i]) {
			break;
		}
		free(arr[i]);
	}
	free(arr);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}
	if (n == 0) {
		printf("res: 0, time: 0.00 seconds\n");
		return EXIT_SUCCESS;
	}

	int status = EXIT_FAILURE;
	int **a = malloc(sizeof(*a) * n);
	if (!a) PERROR_GOTO(error_a);              // FIXED: check outer malloc before macro
	INIT_ARRAY(a, error_a);

	int **b = malloc(sizeof(*b) * n);
	if (!b) PERROR_GOTO(error_b);
	INIT_ARRAY(b, error_b);

	int **c = malloc(sizeof(*c) * n);
	if (!c) PERROR_GOTO(error_c);
	INIT_ARRAY(c, error_c);

	status = EXIT_SUCCESS;

	// fill matrices a and b with random values
	// FIXED: made random number generation thread-safe
	srand(7);
	#pragma omp parallel
	{
		unsigned int seed = 7 + omp_get_thread_num();
		#pragma omp for collapse(2)
		for (long i = 0; i < n; ++i) {
			for (long j = 0; j < n; ++j) {
				a[i][j] = rand_r(&seed);
				b[i][j] = rand_r(&seed);
			}
		}
	}
	double start_time = omp_get_wtime();
	// FIXED: Moved the summation of the result into the parallel region
	// FIXED: Removed incorrect nested parallel region
	// FIXED: Use OpenMP reduction instead of manual thread-local accumulation
	unsigned long res = 0;
	#pragma omp parallel for reduction(+:res) default(none) shared(n, a, b, c)
	for(long i = 0; i < n; ++i;){
		for(long k = 0; k < n; ++k){
			for(long j = 0; j < n; ++j){
				c[i][j] += a[i][k] * b[k][j]; // standard matrix multiplication
				res += c[i][j];
			}
		}
	}

	double end_time = omp_get_wtime();
	printf("res: %lu, time: %2.2f seconds\n", res, end_time - start_time);

	// cleanup
	free(local_res);
error_c:
	free_2d_array(c, n);
error_b:
	free_2d_array(b, n);
error_a:
	free_2d_array(a, n);
	return status;
}
