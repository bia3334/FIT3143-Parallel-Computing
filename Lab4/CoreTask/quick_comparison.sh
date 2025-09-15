#!/bin/bash

# Quick comparison script for Lab4 vs Lab2
echo "=== Quick Performance Comparison ==="
echo "Lab 4 MPI vs Lab 2 (Threads/OpenMP) vs Serial"
echo ""

# Test parameters
N=10000000

echo "Testing with N = $N"
echo ""

# Serial (Lab4)
echo "1. Serial (Lab4):"
./serial_prime $N | grep "Total execution time"

# MPI (various process counts)
echo ""
echo "2. MPI Performance:"
for procs in 2 4 8; do
    echo "  $procs processes:"
    mpirun -np $procs ./mpi_prime $N | grep "Total execution time"
done

# Compare with Lab2 if available
LAB2_PATH="../../Lab2"

if [ -f "$LAB2_PATH/task1" ]; then
    echo ""
    echo "3. Lab2 Serial Comparison:"
    echo "$N" | $LAB2_PATH/task1 | grep -E "(Time taken|execution time)"
fi

if [ -f "$LAB2_PATH/task2" ]; then
    echo ""
    echo "4. Lab2 POSIX Threads:"
    for threads in 2 4 8; do
        echo "  $threads threads:"
        echo -e "$N\n$threads" | $LAB2_PATH/task2 | grep -E "(Time taken|execution time)"
    done
fi

if [ -f "$LAB2_PATH/task3" ]; then
    echo ""
    echo "5. Lab2 OpenMP:"
    for threads in 2 4 8; do
        echo "  $threads threads:"
        echo -e "$N\n$threads" | $LAB2_PATH/task3 | grep -E "(Time taken|execution time)"
    done
fi

echo ""
echo "=== Analysis ==="
echo "- Communication overhead is significant for MPI"
echo "- Shared memory (Lab2) should outperform distributed memory (Lab4) for single machine"
echo "- MPI advantages appear with larger problem sizes or multiple machines"
