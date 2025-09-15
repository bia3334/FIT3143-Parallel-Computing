# FIT3143 - Parallel Computing
## Monash University Course Projects

A comprehensive collection of parallel computing implementations and performance analysis for FIT3143 (Parallel Computing) course.

## 📚 Course Overview

This repository contains practical implementations exploring various parallel computing paradigms, performance optimization techniques, and comparative analysis across different parallelization approaches.

**Course:** FIT3143 - Parallel Computing  
**Institution:** Monash University  
**Academic Year:** S2-2025

## 🗂️ Project Structure

```
FIT3143-Parallel-Computing/
├── README.md                    # This file - Project overview
├── Lab2/                        # ✅ Threads & OpenMP
│   ├── README.md               # Lab-specific documentation
│   ├── Lab2_Report.md          # Comprehensive technical report
│   ├── task1.c                 # Serial implementation
│   ├── task2.c                 # POSIX Threads implementation
│   ├── task3.c                 # OpenMP implementation
│   ├── primes_*.txt            # Output files
│   └── compiled executables
├── Lab3/                        # ✅ Message Passing Interface (MPI)
│   ├── README.md               # Lab-specific documentation
│   ├── helloworld.c            # Basic MPI Hello World
│   ├── task2a.c                # MPI Send/Recv communication
│   ├── task2b.c                # MPI Broadcast communication
│   ├── task3.c                 # MPI custom datatypes
│   ├── task4.c                 # MPI Pack/Unpack
│   ├── task5.c                 # Parallel Pi calculation
│   ├── serial_pi.c             # Serial Pi for comparison
│   ├── Makefile                # Build configuration
│   └── compiled executables
├── Lab4/                        # ✅ MPI Prime Search & CAAS Cluster
│   ├── LAB4_FINAL_REPORT.md    # Comprehensive final report
│   ├── CoreTask/               # Local machine MPI implementation
│   │   ├── mpi_prime.c         # MPI prime search algorithm
│   │   ├── serial_prime.c      # Serial baseline for comparison
│   │   ├── Makefile            # Build configuration
│   │   ├── performance_analysis.sh # Automated benchmarking
│   │   └── theoretical_analysis.md # Amdahl's Law analysis
│   └── CAAS/                   # Cluster computing extended task
│       ├── *_caas.c            # Cluster-adapted implementations
│       ├── job_*.slurm         # SLURM job scripts
│       ├── *_results.out       # Cluster execution results
│       └── CAAS_PERFORMANCE_ANALYSIS.md # Cluster analysis
└── Lab5/                        # 🚧 [Future Lab - TBD]
```

## 🧪 Completed Labs

### Lab 2: Threads & OpenMP - Prime Number Finding ✅
**Status:** Completed  
**Focus:** Comparative study of parallel computing approaches

**Implementations:**
- Serial baseline algorithm
- POSIX Threads (manual threading)
- OpenMP (high-level parallelization)

**Key Results:**
- **Best Performance:** OpenMP with 8 threads (3.00x speedup)
- **Worst Performance:** POSIX Threads (0.45x-0.65x - performance degradation)
- **Algorithm:** Prime number detection up to n=1,000,000

**Files:** `task1.c`, `task2.c`, `task3.c`, comprehensive documentation

[📖 View Lab 2 Details →](./Lab2/README.md)

### Lab 3: Message Passing Interface (MPI) ✅
**Status:** Completed  
**Focus:** Distributed memory parallel computing with MPI

**Implementations:**
- Basic MPI Hello World program
- Point-to-point communication (Send/Recv)
- Collective communication (Broadcast)
- Custom MPI datatypes and data packing
- Parallel Pi approximation using numerical integration

**Key Results:**
- **Best Performance:** Pi calculation with 4 processes (250.4x speedup for N=1M)
- **Communication Patterns:** Collective operations outperform point-to-point
- **Algorithm:** Numerical integration of 4/(1+x²) from 0 to 1

**Files:** `helloworld.c`, `task2a.c`, `task2b.c`, `task3.c`, `task4.c`, `task5.c`, `serial_pi.c`

[📖 View Lab 3 Details →](./Lab3/README.md)

### Lab 4: MPI Prime Search & CAAS Cluster Computing ✅
**Status:** Completed  
**Focus:** Advanced MPI implementation and cluster performance analysis

**Implementations:**
- MPI prime search with cyclic workload distribution
- Serial baseline for performance comparison
- CAAS cluster deployment (Serial, OpenMP, MPI configurations)
- Theoretical speedup analysis using Amdahl's Law with fabric time

**Key Results:**
- **Local Machine MPI:** 0.09x speedup (poor due to communication overhead)
- **CAAS OpenMP:** 9.26x speedup with 16 threads (excellent scaling)
- **CAAS vs Local:** 4x slower per-core but 2-4x more cores available
- **Problem Size Impact:** Small problems favor shared memory over distributed memory

**Files:** `mpi_prime.c`, `serial_prime.c`, CAAS job scripts, comprehensive performance analysis

[📖 View Lab 4 Details →](./Lab4/LAB4_FINAL_REPORT.md)

## 🚧 Upcoming Labs

### Lab 5: [Topic TBD]
**Status:** Pending  
**Expected Focus:** [Will be updated when lab content is available]

## 🎯 Learning Objectives

Throughout this course, the following parallel computing concepts are explored:

### Core Concepts
- **Threading Models:** POSIX Threads vs OpenMP
- **Message Passing:** MPI communication patterns and collective operations
- **Distributed Computing:** Cluster computing with CAAS platform
- **Performance Analysis:** Speed-up, efficiency, scalability metrics
- **Load Balancing:** Static vs dynamic task distribution, cyclic distribution
- **Memory Management:** Shared vs distributed memory architectures
- **Synchronization:** Critical sections, race conditions, deadlocks
- **Data Distribution:** Point-to-point vs collective communication strategies
- **Fabric Time:** Communication overhead in distributed systems

### Technical Skills
- **Algorithm Parallelization:** Converting serial to parallel algorithms
- **MPI Programming:** Distributed computing with message passing
- **Cluster Computing:** SLURM job scheduling, multi-node deployment
- **Communication Optimization:** Choosing efficient MPI operations
- **Performance Profiling:** Timing, bottleneck identification
- **Optimization Techniques:** Cache locality, NUMA awareness
- **Comparative Analysis:** Multi-approach evaluation methodology
- **Theoretical Analysis:** Amdahl's Law, Gustafson's Law, fabric time modeling

## 🔧 Development Environment

### System Requirements
- **OS:** Linux (tested on WSL2)
- **Compiler:** GCC with OpenMP support, MPI compiler (mpicc)
- **MPI Implementation:** OpenMPI or MPICH
- **Architecture:** x86_64
- **Cores:** Multi-core system recommended (tested on 20-core system)

### Setup Instructions
```bash
# Install required packages
sudo apt update
sudo apt install gcc build-essential openmpi-bin openmpi-common libopenmpi-dev

# Verify OpenMP support
gcc --version
echo | gcc -fopenmp -dM -E - | grep -i openmp

# Verify MPI installation
mpicc --version
mpirun --version
```

### Common Compilation Patterns
```bash
# Serial programs
gcc -o program program.c -lm

# POSIX Threads
gcc -o program program.c -lpthread -lm

# OpenMP
gcc -o program program.c -fopenmp -lm

# MPI programs
mpicc -o program program.c -lm

# With optimization (recommended for performance testing)
gcc -O3 -o program program.c -fopenmp -lm
mpicc -O3 -o program program.c -lm
```

## 📊 Performance Methodology

### Standard Testing Approach
1. **Baseline Establishment:** Serial implementation timing
2. **Parallel Implementations:** Multiple approaches tested
3. **Scalability Analysis:** Various thread counts evaluated
4. **Statistical Validity:** Multiple runs, average results
5. **Comparative Analysis:** Speed-up and efficiency calculations

### Metrics Used
- **Execution Time:** Wall-clock time measurement
- **Speed-up:** T_serial / T_parallel
- **Efficiency:** Speed-up / Number_of_threads × 100%
- **Scalability:** Performance trends across thread counts

## 🏆 Key Findings Summary

### Lab 2 Highlights
- **OpenMP demonstrates superior performance** over manual threading
- **Dynamic scheduling outperforms static partitioning** for irregular workloads
- **Optimal thread count** doesn't always equal available cores
- **Memory management strategy** critically impacts parallel performance

### Lab 3 Highlights
- **Collective operations (MPI_Bcast) outperform point-to-point** communication
- **MPI custom datatypes** provide elegant solution for complex data structures
- **Exceptional speedup results** (250x) due to cache effects and memory bandwidth utilization
- **Domain decomposition** scales effectively for numerical integration problems

### Lab 4 Highlights
- **Problem size critically affects MPI performance** - small problems favor shared memory
- **CAAS cluster provides excellent OpenMP scaling** (9.26x speedup @ 16 threads)
- **Communication overhead dominates MPI** for prime search (n=1M)
- **Cluster per-core performance differs significantly** from local machines (4x slower)
- **Theoretical vs actual performance** - fabric time must be considered

## 📈 Course Progress

- [x] **Lab 2:** Threads & OpenMP (Completed)
- [x] **Lab 3:** Message Passing Interface (Completed)
- [x] **Lab 4:** MPI Prime Search & CAAS Cluster (Completed)
- [ ] **Lab 5:** [Pending]

## 🔗 Quick Navigation

| Lab | Topic | Status | Key Files | Performance Highlights |
|-----|-------|--------|-----------|----------------------|
| [Lab 2](./Lab2/) | Threads & OpenMP | ✅ Complete | `task1.c`, `task2.c`, `task3.c` | 3.00x speedup (OpenMP) |
| [Lab 3](./Lab3/) | Message Passing Interface | ✅ Complete | `helloworld.c`, `task2a.c`, `task2b.c`, `task3.c`, `task4.c`, `task5.c` | 250.4x speedup (MPI Pi calc) |
| [Lab 4](./Lab4/) | MPI Prime Search & CAAS | ✅ Complete | `mpi_prime.c`, `serial_prime.c`, CAAS jobs | 9.26x speedup (CAAS OpenMP) |
| Lab 5 | TBD | 🚧 Pending | - | - |

## 📝 Documentation Standards

Each lab maintains consistent documentation:
- **README.md:** Quick start guide and overview
- **Report.md:** Comprehensive technical analysis
- **Source code:** Well-commented implementations
- **Output files:** Sample results and verification data

## 🤝 Academic Integrity

This repository contains academic work for educational purposes. All implementations are original work completed according to Monash University academic integrity guidelines.

**Note:** Code may be referenced for learning purposes, but direct copying for academic submissions violates academic integrity policies.

## 📧 Contact Information

**Student:** Tien Hung Nguyen
**Student ID:** 35499435
**Email:** tngu0534@student.monash.edu  
**Course:** FIT3143 - Parallel Computing  
**Institution:** Monash University

---

## 📄 License

Educational use only - Monash University FIT3143 Course Material

---

**Last Updated:** September 2025  
**Repository Status:** Active Development (Labs 2-4 Complete, Lab 5 Pending)
