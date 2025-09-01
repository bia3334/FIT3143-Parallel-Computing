#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;
    int value;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    do {
        if (rank == 0) {
            // Process 0 reads input from user
            printf("Enter an integer (negative to quit): ");
            fflush(stdout);
            scanf("%d", &value);
        }
        
        // Broadcast the value from process 0 to all processes
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        // All processes print their rank and the value received
        if (value >= 0) {
            printf("Process %d received value: %d\n", rank, value);
            fflush(stdout);
        }
        
    } while (value >= 0);
    
    MPI_Finalize();
    return 0;
}
