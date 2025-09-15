#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
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

// Simple cyclic workload distribution  
// Each process gets every size-th number starting from (rank + 2)
void calculate_workload_range(int rank, int size, int n, int *start, int *end) {
    // Simple cyclic distribution: 
    // Process 0: 2, 2+size, 2+2*size, ...
    // Process 1: 3, 3+size, 3+2*size, ...
    // Process 2: 4, 4+size, 4+2*size, ...
    *start = rank + 2;
    *end = n;
}

// Count how many numbers this process will check (for memory allocation)
int count_workload_size(int rank, int size, int n) {
    int count = 0;
    
    // Use simple cyclic distribution: each process checks every size-th number
    // starting from (rank + 2)
    for (int i = rank + 2; i < n; i += size) {
        count++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int n;
    double start_time, end_time, compute_time, comm_time;
    double total_start, total_end;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    total_start = MPI_Wtime();
    
    // Root process reads command line argument
    if (rank == 0) {
        if (argc != 2) {
            printf("Usage: %s <n>\n", argv[0]);
            printf("Where n is the upper limit for prime search\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        n = atoi(argv[1]);
        if (n <= 2) {
            printf("Error: n must be greater than 2\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        printf("Searching for primes less than %d using %d MPI processes\n", n, size);
    }
    
    // Broadcast n to all processes
    double bcast_start = MPI_Wtime();
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    double bcast_end = MPI_Wtime();
    
    // Calculate workload for this process
    int local_start, local_end;
    calculate_workload_range(rank, size, n, &local_start, &local_end);
    
    // Allocate memory for local primes
    int max_local_primes = count_workload_size(rank, size, n);
    int *local_primes = malloc(max_local_primes * sizeof(int));
    if (!local_primes) {
        printf("Process %d: Memory allocation failed\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    // Synchronize all processes before computation
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    
    // Each process finds primes in its assigned range using cyclic distribution
    int local_count = 0;
    
    // Simple cyclic distribution - each process checks every size-th number
    for (int i = local_start; i < local_end; i += size) {
        if (is_prime(i)) {
            local_primes[local_count++] = i;
        }
    }
    
    end_time = MPI_Wtime();
    compute_time = end_time - start_time;
    
    // Communication phase: gather results
    double comm_start = MPI_Wtime();
    
    // First, gather the counts from all processes
    int *all_counts = NULL;
    if (rank == 0) {
        all_counts = malloc(size * sizeof(int));
    }
    MPI_Gather(&local_count, 1, MPI_INT, all_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Calculate displacements for MPI_Gatherv
    int *displs = NULL;
    int total_primes = 0;
    if (rank == 0) {
        displs = malloc(size * sizeof(int));
        displs[0] = 0;
        total_primes = all_counts[0];
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i-1] + all_counts[i-1];
            total_primes += all_counts[i];
        }
    }
    
    // Gather all primes using MPI_Gatherv
    int *all_primes = NULL;
    if (rank == 0) {
        all_primes = malloc(total_primes * sizeof(int));
    }
    
    MPI_Gatherv(local_primes, local_count, MPI_INT, 
                all_primes, all_counts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    
    double comm_end = MPI_Wtime();
    comm_time = comm_end - comm_start;
    
    // Root process sorts and writes results
    if (rank == 0) {
        // Sort the gathered primes (due to block-cyclic distribution, they may be out of order)
        for (int i = 0; i < total_primes - 1; i++) {
            for (int j = i + 1; j < total_primes; j++) {
                if (all_primes[i] > all_primes[j]) {
                    int temp = all_primes[i];
                    all_primes[i] = all_primes[j];
                    all_primes[j] = temp;
                }
            }
        }
        
        // Write results to file
        FILE *outfile = fopen("primes_mpi.txt", "w");
        if (!outfile) {
            perror("File opening failed");
        } else {
            for (int i = 0; i < total_primes; i++) {
                fprintf(outfile, "%d\n", all_primes[i]);
            }
            fclose(outfile);
            printf("Primes written to primes_mpi.txt\n");
        }
        
        total_end = MPI_Wtime();
        
        // Print timing results
        printf("\n=== PERFORMANCE RESULTS ===\n");
        printf("Total primes found: %d\n", total_primes);
        printf("Total execution time: %.6f seconds\n", total_end - total_start);
        printf("Broadcast time: %.6f seconds\n", bcast_end - bcast_start);
        printf("Root process computation time: %.6f seconds\n", compute_time);
        printf("Communication time: %.6f seconds\n", comm_time);
        printf("===========================\n");
        
        // Cleanup root-specific memory
        free(all_counts);
        free(displs);
        free(all_primes);
    } else {
        // Non-root processes print their timing information
        printf("Process %d: Computation time: %.6f seconds, Communication time: %.6f seconds\n", 
               rank, compute_time, comm_time);
    }
    
    // Cleanup
    free(local_primes);
    
    // Finalize MPI
    MPI_Finalize();
    return 0;
}
