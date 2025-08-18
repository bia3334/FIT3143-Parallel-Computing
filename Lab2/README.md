# FIT3143 Lab 2: Threads & OpenMP - Prime Number Finding

A comparative study of parallel computing approaches using POSIX Threads and OpenMP for finding prime numbers.

## 🎯 Project Overview

This project implements and compares three different approaches to find prime numbers:
- **Serial Implementation** (baseline)
- **POSIX Threads** (manual threading)
- **OpenMP** (high-level parallelization)

## 📊 Performance Results

| Method | Threads | Time (s) | Speed-up | Efficiency |
|--------|---------|----------|----------|------------|
| **Serial** | 1 | 0.0723 | 1.00x | 100% |
| **POSIX Threads** | 4 | 0.1169 | 0.62x | 15.5% |
| **POSIX Threads** | 8 | 0.1109 | 0.65x | 8.1% |
| **POSIX Threads** | 16 | 0.1595 | 0.45x | 2.8% |
| **OpenMP** | 4 | 0.0341 | 2.12x | 53% |
| **OpenMP** | 8 | 0.0241 | **3.00x** | 37.5% |
| **OpenMP** | 16 | 0.0653 | 1.11x | 6.9% |

**🏆 Best Performance:** OpenMP with 8 threads (3.00x speedup)

## 🚀 Quick Start

### Prerequisites
```bash
sudo apt update
sudo apt install gcc build-essential
```

### Compilation
```bash
# Serial version
gcc -o task1 task1.c -lm

# POSIX Threads version
gcc -o task2 task2.c -lpthread -lm

# OpenMP version
gcc -o task3 task3.c -fopenmp -lm
```

### Execution
```bash
# Run each version
./task1  # Enter n (e.g., 1000000)
./task2  # Enter n and number of threads
./task3  # Enter n and number of threads
```

## 📁 Project Structure

```
Lab2/
├── README.md                 # This file
├── Lab2_Report.md           # Comprehensive technical report
├── task1.c                  # Serial implementation
├── task2.c                  # POSIX Threads implementation
├── task3.c                  # OpenMP implementation
├── primes_serial.txt        # Output from serial version
├── primes_parallel.txt      # Output from POSIX threads
├── primes_openmp.txt        # Output from OpenMP
└── .gitignore              # Git ignore rules
```

## 🔬 Algorithm Details

### Prime Detection Algorithm
All implementations use an optimized prime checking algorithm:
- Check divisibility only up to √n
- Skip even numbers (except 2)
- Test only odd divisors

```c
int is_prime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int limit = (int)sqrt(num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}
```

## 🧵 Implementation Approaches

### 1. Serial Implementation (task1.c)
- Straightforward sequential execution
- Baseline for performance comparison
- Single-threaded prime finding

### 2. POSIX Threads (task2.c)
- **Strategy:** Static range partitioning
- **Memory:** Per-thread allocation
- **Issue:** Performance degradation due to overhead

### 3. OpenMP (task3.c)
- **Strategy:** Dynamic scheduling
- **Memory:** Shared array with critical sections
- **Advantage:** Superior load balancing

## 📈 Key Findings

### ✅ OpenMP Advantages
- **3.00x speedup** with optimal configuration
- Dynamic load balancing
- Lower runtime overhead
- Better memory management
- Compiler optimizations

### ❌ POSIX Threads Issues
- **Performance degradation** in all test cases
- Static partitioning causes load imbalance
- Memory fragmentation problems
- High thread management overhead

### 🎯 Optimal Configuration
- **8 threads** provide peak performance
- **Dynamic scheduling** > Static partitioning
- **Shared memory** > Per-thread allocation

## 🔧 System Specifications

- **CPU Cores:** 20 available
- **Architecture:** x86_64  
- **OS:** Linux (WSL2)
- **Test Size:** n = 1,000,000
- **Primes Found:** 78,498

## 📚 Learning Objectives

This lab demonstrates:
- Parallel algorithm design principles
- Performance analysis and optimization
- Comparison of threading approaches
- Scalability considerations
- Load balancing strategies

## 🤝 Contributing

This is an academic project for FIT3143 (Parallel Computing). For educational purposes and reference only.

## 📄 License

Educational use only - Monash University FIT3143

---

**Author:** [Your Name]  
**Student ID:** [Your ID]  
**Course:** FIT3143 - Parallel Computing  
**Institution:** Monash University
