#!/bin/bash
#SBATCH --job-name=prime_openmp_single
#SBATCH --time=00:10:00
#SBATCH --mem=16G
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --ntasks-per-node=1
#SBATCH --partition=defq
#SBATCH --output=openmp_single_%j.out
#SBATCH --error=openmp_single_%j.err

# CAAS OpenMP Prime Search Job - Single Node
# Student: Tien Hung Nguyen (35499435)
# Lab 4 Extended Task - Test with x = 2, 4, 8, 16 threads

echo "=== CAAS OpenMP Prime Search - Single Node ==="
echo "Job ID: $SLURM_JOB_ID"
echo "Node: $SLURMD_NODENAME"
echo "CPUs per task: $SLURM_CPUS_PER_TASK"
echo "Start time: $(date)"
echo ""

# Set problem size
N=1000000

echo "Problem size: N = $N"

# Test with different thread counts: x = 2, 4, 8, 16
THREAD_COUNTS=(2 4 8 16)

for threads in "${THREAD_COUNTS[@]}"; do
    echo "----------------------------------------"
    echo "Testing with $threads threads..."
    echo "Setting OMP_NUM_THREADS=$threads"
    
    export OMP_NUM_THREADS=$threads
    
    # Run OpenMP version
    ./openmp_prime_caas $N $threads
    
    echo "Completed $threads threads test"
    echo ""
done

echo "End time: $(date)"
echo "=== OpenMP Single Node Job Completed ==="
