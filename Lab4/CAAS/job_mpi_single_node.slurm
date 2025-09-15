#!/bin/bash
#SBATCH --job-name=prime_mpi_single
#SBATCH --time=00:10:00
#SBATCH --mem=16G
#SBATCH --ntasks=16
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=16
#SBATCH --partition=defq
#SBATCH --output=mpi_single_%j.out
#SBATCH --error=mpi_single_%j.err

# CAAS MPI Prime Search Job - Single Node
# Student: Tien Hung Nguyen (35499435)
# Lab 4 Extended Task - Test with x = 2, 4, 8, 16 processes on single node

echo "=== CAAS MPI Prime Search - Single Node ==="
echo "Job ID: $SLURM_JOB_ID"
echo "Node: $SLURMD_NODENAME"
echo "Total tasks: $SLURM_NTASKS"
echo "Start time: $(date)"
echo ""

# Set problem size
N=1000000

echo "Problem size: N = $N"

# Test with different process counts: x = 2, 4, 8, 16
PROCESS_COUNTS=(2 4 8 16)

# Load MPI module as per CAAS requirements
module load openmpi/4.1.5-gcc-11.2.0-ux65npg

for procs in "${PROCESS_COUNTS[@]}"; do
    echo "----------------------------------------"
    echo "Testing with $procs MPI processes on single node..."
    
    # Run MPI version using srun
    srun -n $procs ./mpi_prime_caas $N
    
    echo "Completed $procs processes test"
    echo ""
done

echo "End time: $(date)"
echo "=== MPI Single Node Job Completed ==="
