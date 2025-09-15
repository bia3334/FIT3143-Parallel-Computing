#!/bin/bash
#SBATCH --job-name=prime_mpi_multi
#SBATCH --time=00:10:00
#SBATCH --mem=16G
#SBATCH --nodes=2
#SBATCH --ntasks=32
#SBATCH --ntasks-per-node=16
#SBATCH --cpus-per-task=1
#SBATCH --partition=defq
#SBATCH --output=mpi_multi_%j.out
#SBATCH --error=mpi_multi_%j.err

# CAAS MPI Prime Search Job - Multi Node
# Student: Tien Hung Nguyen (35499435)
# Lab 4 Extended Task - Test with 2x processes on 2 nodes (x processes per node)

echo "=== CAAS MPI Prime Search - Multi Node ==="
echo "Job ID: $SLURM_JOB_ID"
echo "Nodes: $SLURM_JOB_NUM_NODES"
echo "Tasks per node: $SLURM_NTASKS_PER_NODE"
echo "Total tasks: $SLURM_NTASKS"
echo "Node list: $SLURM_JOB_NODELIST"
echo "Start time: $(date)"
echo ""

# Set problem size
N=1000000

echo "Problem size: N = $N"

# Test with different process counts: 2x processes on 2 nodes
# x = 2, 4, 8, 16 → Total processes = 4, 8, 16, 32
PROCESS_CONFIGS=(
    "4:2"   # 4 total processes, 2 per node
    "8:4"   # 8 total processes, 4 per node
    "16:8"  # 16 total processes, 8 per node
    "32:16" # 32 total processes, 16 per node
)

# Load MPI module as per CAAS requirements
module load openmpi/4.1.5-gcc-11.2.0-ux65npg

for config in "${PROCESS_CONFIGS[@]}"; do
    IFS=':' read -r total_procs procs_per_node <<< "$config"
    
    echo "----------------------------------------"
    echo "Testing with $total_procs total MPI processes ($procs_per_node per node, 2 nodes)"
    echo "Configuration: 2 nodes × $procs_per_node processes = $total_procs total"
    
    # Run MPI version across multiple nodes using srun
    srun -n $total_procs ./mpi_prime_caas $N
    
    echo "Completed $total_procs processes test"
    echo ""
done

echo "End time: $(date)"
echo "=== MPI Multi Node Job Completed ==="
