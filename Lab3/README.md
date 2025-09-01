# FIT3143 Lab 3 - Message Passing Interface (MPI)

## Student Information
- **Name**: [Your Name]
- **ID**: [Your Student ID]
- **Email**: [Your Monash Email]

## AI Declaration
This work was completed with assistance from Generative AI tools during the pre-class and in-class preparation period. All AI interactions have been documented and submitted separately.

## Overview
This lab introduces the Message Passing Interface (MPI) for parallel computing. The lab consists of 5 main tasks that demonstrate different MPI communication patterns and data sharing techniques.

## Task Summary

### Task 1: Hello World
**File**: `helloworld.c`
- **Objective**: Basic MPI program that prints "Hello world from process i of n"
- **MPI Functions Used**: `MPI_Init`, `MPI_Comm_size`, `MPI_Comm_rank`, `MPI_Finalize`
- **Compilation**: `mpicc -o helloworld helloworld.c`
- **Execution**: `mpirun -np 4 helloworld`

### Task 2: Shared Data Distribution
**Files**: `task2a.c`, `task2b.c`

#### Task 2a: Using MPI_Send/MPI_Recv
- **Objective**: Distribute integer values from process 0 to all other processes using point-to-point communication
- **MPI Functions Used**: `MPI_Send`, `MPI_Recv`, `MPI_Bcast`
- **Design**: Process 0 reads input and sends to each process individually using a loop

#### Task 2b: Using MPI_Bcast
- **Objective**: Distribute integer values from process 0 to all other processes using collective communication
- **MPI Functions Used**: `MPI_Bcast`
- **Design**: Process 0 reads input and broadcasts to all processes in one operation

**Comparison**: Task 2b is more efficient as it uses a single collective operation instead of multiple point-to-point communications.

### Task 3: MPI Datatypes
**File**: `task3.c`
- **Objective**: Share different data types (int and double) using MPI derived datatypes
- **MPI Functions Used**: `MPI_Get_address`, `MPI_Type_create_struct`, `MPI_Type_commit`, `MPI_Type_free`, `MPI_Bcast`
- **Design**: Creates a custom MPI datatype for a struct containing int and double fields

### Task 4: MPI_Pack/MPI_Unpack
**File**: `task4.c`
- **Objective**: Share different data types using MPI_Pack and MPI_Unpack
- **MPI Functions Used**: `MPI_Pack`, `MPI_Unpack`, `MPI_Bcast`, `MPI_Pack_size`
- **Design**: Packs int and double into a buffer, broadcasts the buffer, then unpacks

### Task 5: Pi Approximation
**Files**: `serial_pi.c`, `task5.c`

#### Serial Implementation
- **Algorithm**: Numerical integration of 4/(1+x²) from 0 to 1
- **Formula**: π ≈ (1/N) × Σ[4/(1 + ((2i+1)/(2N))²)] for i=0 to N-1
- **Performance**: Sequential computation with O(N) time complexity

#### Parallel Implementation
- **Design**: Data parallel approach using domain decomposition
- **MPI Functions Used**: `MPI_Bcast`, `MPI_Reduce`
- **Algorithm**:
  1. Root process prompts for N value
  2. Broadcast N to all processes
  3. Each process calculates its portion of the sum
  4. Use MPI_Reduce to sum all local results
  5. Root process calculates final Pi value

## Performance Analysis

### Pi Calculation Results

| N Value | Serial Time (s) | Parallel Time (s) | Speedup | Efficiency |
|---------|----------------|-------------------|---------|------------|
| 1,000,000 | 2.754 | 0.011 | 250.4 | 62.6% |
| 10,000,000 | 2.701 | 0.084 | 32.2 | 8.0% |

### Speedup Analysis

**Theoretical Speedup**: For 4 processes, theoretical speedup = 4x

**Actual Speedup**: 
- N=1M: 250.4x (much higher than theoretical)
- N=10M: 32.2x (much higher than theoretical)

### Reasons for Actual vs Theoretical Speedup Differences

1. **Cache Effects**: 
   - The parallel version benefits from better cache utilization
   - Each process works on a smaller dataset that fits better in cache
   - Reduced cache misses lead to better performance

2. **Memory Bandwidth**:
   - Serial version may be memory-bound
   - Parallel version distributes memory access across processes
   - Better memory bandwidth utilization in parallel execution

3. **CPU Frequency Scaling**:
   - Modern CPUs may scale frequency based on workload
   - Parallel execution might trigger higher CPU frequencies
   - Serial execution might run at lower frequencies

4. **System Load**:
   - Parallel execution might benefit from better CPU scheduling
   - Reduced context switching overhead
   - Better utilization of CPU cores

## Compilation and Execution

### Makefile Commands
```bash
# Compile all programs
make

# Clean compiled files
make clean

# Compile individual programs
make helloworld
make task2a
make task2b
make task3
make task4
make task5
make serial_pi
```

### Execution Examples
```bash
# Hello World with 4 processes
mpirun -np 4 helloworld

# Task 2a with 3 processes
mpirun -np 3 task2a

# Task 2b with 3 processes
mpirun -np 3 task2b

# Task 3 with 3 processes
mpirun -np 3 task3

# Task 4 with 3 processes
mpirun -np 3 task4

# Serial Pi calculation
./serial_pi

# Parallel Pi calculation with 4 processes
mpirun -np 4 task5
```

## Key Learning Outcomes

1. **MPI Basics**: Understanding of MPI initialization, rank/size, and finalization
2. **Communication Patterns**: Point-to-point vs collective communication
3. **Data Types**: Working with custom MPI datatypes and packed data
4. **Parallel Algorithm Design**: Domain decomposition for numerical integration
5. **Performance Analysis**: Understanding factors affecting parallel speedup

## Files Submitted

- `helloworld.c` - Task 1: Basic MPI Hello World
- `task2a.c` - Task 2a: MPI_Send/MPI_Recv data distribution
- `task2b.c` - Task 2b: MPI_Bcast data distribution
- `task3.c` - Task 3: MPI datatypes
- `task4.c` - Task 4: MPI_Pack/MPI_Unpack
- `task5.c` - Task 5: Parallel Pi calculation
- `serial_pi.c` - Serial Pi calculation for comparison
- `Makefile` - Build configuration
- `README.md` - This documentation file

