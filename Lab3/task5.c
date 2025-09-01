#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    long N;
    int i;
    double local_sum = 0.0;
    double global_sum = 0.0;
    double piVal;
    struct timespec start, end;
    double time_taken;
    long start_index, end_index;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Root process prompts for N value
    if (rank == 0) {
        printf("Enter the value of N (e.g., 100000000): ");
        fflush(stdout);
        scanf("%ld", &N);
    }
    
    // Broadcast N to all processes
    MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    
    // Calculate the range of indices for each process
    long chunk_size = N / size;
    start_index = rank * chunk_size;
    end_index = (rank == size - 1) ? N : (rank + 1) * chunk_size;
    
    // Synchronize all processes before timing
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Get current clock time.
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Each process calculates its portion of the sum
    for(i = start_index; i < end_index; i++)
    {
        local_sum += 4.0 / (1 + pow((2.0 * i + 1.0)/(2.0 * N), 2));
    }
    
    // Reduce all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Get the clock current time again
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    
    // Root process calculates final Pi value and prints results
    if (rank == 0) {
        piVal = global_sum / (double)N;
        printf("Calculated Pi value (Parallel-AlgoI) = %12.9f\n", piVal);
        printf("Overall time (s): %lf\n", time_taken); // tp
        printf("Number of processes: %d\n", size);
    }
    
    MPI_Finalize();
    return 0;
}

