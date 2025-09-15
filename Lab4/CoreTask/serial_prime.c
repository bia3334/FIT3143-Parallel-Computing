#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to check if a number is prime
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

int main(int argc, char *argv[]) {
    int n;
    struct timespec start, end;
    double elapsed_time;
    
    // Read command line argument
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        printf("Where n is the upper limit for prime search\n");
        return 1;
    }
    
    n = atoi(argv[1]);
    if (n <= 2) {
        printf("Error: n must be greater than 2\n");
        return 1;
    }
    
    printf("Searching for primes less than %d (serial version)\n", n);
    
    // Allocate memory for storing primes
    int *primes = malloc(n * sizeof(int));
    if (!primes) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    int count = 0;
    
    // Start timing
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Find primes serially
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            primes[count++] = i;
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    
    // Write results to file
    FILE *outfile = fopen("primes_serial.txt", "w");
    if (!outfile) {
        perror("File opening failed");
        free(primes);
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%d\n", primes[i]);
    }
    fclose(outfile);
    
    printf("\n=== SERIAL PERFORMANCE RESULTS ===\n");
    printf("Primes written to primes_serial.txt\n");
    printf("Total primes found: %d\n", count);
    printf("Total execution time: %.6f seconds\n", elapsed_time);
    printf("==================================\n");
    
    free(primes);
    return 0;
}
