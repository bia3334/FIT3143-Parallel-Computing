#!/bin/bash
#SBATCH --job-name=prime_serial
#SBATCH --time=00:10:00
#SBATCH --mem=2G
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=defq
#SBATCH --output=serial_%j.out
#SBATCH --error=serial_%j.err

# CAAS Serial Prime Search Job
# Student: Tien Hung Nguyen (35499435)
# Lab 4 Extended Task

echo "=== CAAS Serial Prime Search Job ==="
echo "Job ID: $SLURM_JOB_ID"
echo "Node: $SLURMD_NODENAME"
echo "Cores per task: $SLURM_CPUS_PER_TASK"
echo "Start time: $(date)"
echo ""

# Set problem size (use same as local testing)
N=1000000

echo "Problem size: N = $N"
echo "Running serial prime search..."

# Run the serial program
./serial_prime_caas $N

echo ""
echo "End time: $(date)"
echo "=== Job Completed ==="
