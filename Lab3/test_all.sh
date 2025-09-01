#!/bin/bash

echo "=== FIT3143 Lab 3 - MPI Test Script ==="
echo "Testing all MPI programs..."
echo

# Test Task 1: Hello World
echo "1. Testing Hello World (4 processes):"
mpirun -np 4 helloworld
echo

# Test Task 2a: MPI_Send/MPI_Recv
echo "2. Testing Task 2a - MPI_Send/MPI_Recv (3 processes):"
echo -e "5\n10\n-1" | mpirun -np 3 task2a
echo

# Test Task 2b: MPI_Bcast
echo "3. Testing Task 2b - MPI_Bcast (3 processes):"
echo -e "5\n10\n-1" | mpirun -np 3 task2b
echo

# Test Task 3: MPI Datatypes
echo "4. Testing Task 3 - MPI Datatypes (3 processes):"
echo -e "5 3.14\n10 2.718\n-1 0" | mpirun -np 3 task3
echo

# Test Task 4: MPI_Pack/MPI_Unpack
echo "5. Testing Task 4 - MPI_Pack/MPI_Unpack (3 processes):"
echo -e "5 3.14\n10 2.718\n-1 0" | mpirun -np 3 task4
echo

# Test Serial Pi
echo "6. Testing Serial Pi calculation:"
echo "   - N=100000"
echo "100000" | ./serial_pi
echo "   - N=1000000"
echo "1000000" | ./serial_pi
echo

# Test Parallel Pi
echo "7. Testing Parallel Pi calculation (4 processes):"
echo "   - N=100000"
echo "100000" | mpirun -np 4 task5
echo "   - N=1000000"
echo "1000000" | mpirun -np 4 task5
echo

echo "=== All tests completed successfully! ==="

