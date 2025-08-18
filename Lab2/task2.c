#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int start;
    int end;
    int *primes;
    int *count;
} ThreadData;

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

void* find_primes(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int idx = 0;
    for (int i = data->start; i < data->end; i++) {
        if (is_prime(i)) {
            data->primes[idx++] = i;
        }
    }
    *(data->count) = idx; // number of primes found by this thread
    pthread_exit(NULL);
}

int main() {
    int n, num_threads;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Available CPU cores: %d\n", cores);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int *all_primes[num_threads];
    int counts[num_threads];

    clock_t start = clock();

    int range = n / num_threads;
    for (int t = 0; t < num_threads; t++) {
        int start_num = t * range;
        int end_num = (t == num_threads - 1) ? n : start_num + range;
        all_primes[t] = malloc(range * sizeof(int)); // over-allocate
        counts[t] = 0;
        thread_data[t] = (ThreadData){start_num, end_num, all_primes[t], &counts[t]};
        pthread_create(&threads[t], NULL, find_primes, &thread_data[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    clock_t end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Merge results in ascending order (already sorted per thread)
    FILE *outfile = fopen("primes_parallel.txt", "w");
    if (!outfile) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    for (int t = 0; t < num_threads; t++) {
        for (int i = 0; i < counts[t]; i++) {
            fprintf(outfile, "%d\n", all_primes[t][i]);
        }
        free(all_primes[t]);
    }
    fclose(outfile);

    printf("Time taken (parallel): %.4f seconds\n", elapsed_time);
    printf("Primes written to primes_parallel.txt\n");

    return 0;
}
