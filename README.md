# FIT3143 - Parallel Computing
## Monash University Course Projects

A comprehensive collection of parallel computing implementations and performance analysis for FIT3143 (Parallel Computing) course.

## 📚 Course Overview

This repository contains practical implementations exploring various parallel computing paradigms, performance optimization techniques, and comparative analysis across different parallelization approaches.

**Course:** FIT3143 - Parallel Computing  
**Institution:** Monash University  
**Academic Year:** [Current Year]

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
├── Lab3/                        # 🚧 [Future Lab - TBD]
├── Lab4/                        # 🚧 [Future Lab - TBD]
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

## 🚧 Upcoming Labs

### Lab 3: [Topic TBD]
**Status:** Pending  
**Expected Focus:** [Will be updated when lab content is available]

### Lab 4: [Topic TBD]
**Status:** Pending  
**Expected Focus:** [Will be updated when lab content is available]

### Lab 5: [Topic TBD]
**Status:** Pending  
**Expected Focus:** [Will be updated when lab content is available]

## 🎯 Learning Objectives

Throughout this course, the following parallel computing concepts are explored:

### Core Concepts
- **Threading Models:** POSIX Threads vs OpenMP
- **Performance Analysis:** Speed-up, efficiency, scalability metrics
- **Load Balancing:** Static vs dynamic task distribution
- **Memory Management:** Shared vs per-thread allocation strategies
- **Synchronization:** Critical sections, race conditions, deadlocks

### Technical Skills
- **Algorithm Parallelization:** Converting serial to parallel algorithms
- **Performance Profiling:** Timing, bottleneck identification
- **Optimization Techniques:** Cache locality, NUMA awareness
- **Comparative Analysis:** Multi-approach evaluation methodology

## 🔧 Development Environment

### System Requirements
- **OS:** Linux (tested on WSL2)
- **Compiler:** GCC with OpenMP support
- **Architecture:** x86_64
- **Cores:** Multi-core system recommended (tested on 20-core system)

### Setup Instructions
```bash
# Install required packages
sudo apt update
sudo apt install gcc build-essential

# Verify OpenMP support
gcc --version
echo | gcc -fopenmp -dM -E - | grep -i openmp
```

### Common Compilation Patterns
```bash
# Serial programs
gcc -o program program.c -lm

# POSIX Threads
gcc -o program program.c -lpthread -lm

# OpenMP
gcc -o program program.c -fopenmp -lm

# With optimization (recommended for performance testing)
gcc -O3 -o program program.c -fopenmp -lm
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

*[Additional findings will be added as more labs are completed]*

## 📈 Course Progress

- [x] **Lab 2:** Threads & OpenMP (Completed)
- [ ] **Lab 3:** [Pending]
- [ ] **Lab 4:** [Pending]
- [ ] **Lab 5:** [Pending]

## 🔗 Quick Navigation

| Lab | Topic | Status | Key Files | Performance Highlights |
|-----|-------|--------|-----------|----------------------|
| [Lab 2](./Lab2/) | Threads & OpenMP | ✅ Complete | `task1.c`, `task2.c`, `task3.c` | 3.00x speedup (OpenMP) |
| Lab 3 | TBD | 🚧 Pending | - | - |
| Lab 4 | TBD | 🚧 Pending | - | - |
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

**Last Updated:** [Current Date]  
**Repository Status:** Active Development (Lab 2 Complete, Labs 3-5 Pending)
