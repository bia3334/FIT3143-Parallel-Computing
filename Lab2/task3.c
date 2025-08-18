#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int is_prime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int limit = (int)sqrt(num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, num_threads;
    printf("Enter n: ");
    scanf("%d", &n);
    
    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Available CPU cores: %d\n", cores);
    
    printf("Enter number of threads (max %d): ", cores);
    scanf("%d", &num_threads);
    
    // Validate and limit thread count
    if (num_threads <= 0) {
        printf("Invalid thread count. Using 1 thread.\n");
        num_threads = 1;
    } else if (num_threads > cores) {
        printf("Thread count exceeds available cores. Limiting to %d threads.\n", cores);
        num_threads = cores;
    }
    printf("Using %d threads\n", num_threads);

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Allocate memory for storing primes
    int *primes = malloc(n * sizeof(int));
    if (!primes) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    int count = 0;

    // Start timing
    double start_time = omp_get_wtime();

    // Using OpenMP parallel for with dynamic scheduling for better load balancing
    #pragma omp parallel for schedule(dynamic, 100)
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            #pragma omp critical
            {
                primes[count++] = i;
            }
        }
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Sort the results (parallel execution doesn't guarantee order)
    if (count > 1) {
        qsort(primes, count, sizeof(int), compare_ints);
    }

    // Write results to file
    FILE *outfile = fopen("primes_openmp.txt", "w");
    if (!outfile) {
        perror("File opening failed");
        free(primes);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%d\n", primes[i]);
    }
    fclose(outfile);

    printf("Time taken (OpenMP): %.4f seconds\n", elapsed_time);
    printf("Total primes found: %d\n", count);
    printf("Primes written to primes_openmp.txt\n");
    printf("Number of threads used: %d\n", num_threads);

    free(primes);
    return 0;
} 