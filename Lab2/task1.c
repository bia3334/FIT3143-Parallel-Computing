#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Available CPU cores: %d\n", cores);

    // Allocate memory for storing primes
    int *primes = malloc(n * sizeof(int));
    if (!primes) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    int count = 0;

    // Start timing
    clock_t start = clock();

    // Find primes serially
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) {
            primes[count++] = i;
        }
    }

    clock_t end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

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

    printf("Time taken (serial): %.4f seconds\n", elapsed_time);
    printf("Total primes found: %d\n", count);
    printf("Primes written to primes_serial.txt\n");

    free(primes);
    return 0;
}