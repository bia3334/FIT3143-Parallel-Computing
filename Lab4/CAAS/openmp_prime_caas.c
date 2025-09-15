#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

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

int main(int argc, char *argv[]) {
    int n, num_threads;
    struct timespec start, end;
    double elapsed_time;
    
    // Read command line arguments
    if (argc != 3) {
        printf("Usage: %s <n> <num_threads>\n", argv[0]);
        printf("Where n is the upper limit and num_threads is the number of OpenMP threads\n");
        return 1;
    }
    
    n = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    
    if (n <= 2) {
        printf("Error: n must be greater than 2\n");
        return 1;
    }
    
    if (num_threads <= 0) {
        printf("Error: num_threads must be greater than 0\n");
        return 1;
    }
    
    printf("CAAS OpenMP Prime Search - n=%d, threads=%d\n", n, num_threads);
    
    // Set number of threads
    omp_set_num_threads(num_threads);
    
    // Allocate memory for storing primes (over-allocate for safety)
    int *primes = malloc(n * sizeof(int));
    if (!primes) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    // Start timing
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int count = 0;
    
    // OpenMP parallel region with dynamic scheduling
    #pragma omp parallel
    {
        int *local_primes = malloc(n * sizeof(int));
        int local_count = 0;
        
        #pragma omp for schedule(dynamic, 100)
        for (int i = 2; i < n; i++) {
            if (is_prime(i)) {
                local_primes[local_count++] = i;
            }
        }
        
        // Critical section to combine results
        #pragma omp critical
        {
            for (int j = 0; j < local_count; j++) {
                primes[count++] = local_primes[j];
            }
        }
        
        free(local_primes);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    
    // Sort results
    qsort(primes, count, sizeof(int), compare_ints);
    
    // Write results to file
    FILE *outfile = fopen("primes_openmp_caas.txt", "w");
    if (!outfile) {
        perror("File opening failed");
        free(primes);
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%d\n", primes[i]);
    }
    fclose(outfile);
    
    printf("\n=== CAAS OPENMP PERFORMANCE RESULTS ===\n");
    printf("Primes written to primes_openmp_caas.txt\n");
    printf("Total primes found: %d\n", count);
    printf("Number of threads: %d\n", num_threads);
    printf("Total execution time: %.6f seconds\n", elapsed_time);
    printf("======================================\n");
    
    free(primes);
    return 0;
}
