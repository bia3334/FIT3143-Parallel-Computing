#!/bin/bash

# Performance Analysis Script for Lab4 MPI Prime Search
# FIT3143 Parallel Computing

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Lab4 MPI Prime Search Performance Analysis ===${NC}"
echo "Author: Tien Hung Nguyen"
echo "Course: FIT3143 Parallel Computing"
echo ""

# Check if programs are compiled
if [ ! -f "mpi_prime" ] || [ ! -f "serial_prime" ]; then
    echo -e "${RED}Error: Programs not compiled. Run 'make' first.${NC}"
    exit 1
fi

# Test parameters
N_VALUES=(100000 1000000 10000000)
PROCESS_COUNTS=(1 2 4 8)
RUNS=3

echo -e "${YELLOW}Performance Analysis Configuration:${NC}"
echo "N values: ${N_VALUES[@]}"
echo "Process counts: ${PROCESS_COUNTS[@]}"
echo "Runs per test: $RUNS"
echo ""

# Create results directory
RESULTS_DIR="performance_results_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$RESULTS_DIR"

# Results file
RESULTS_FILE="$RESULTS_DIR/performance_results.csv"
echo "N,Processes,Run,Serial_Time,MPI_Time,Speedup,Efficiency" > "$RESULTS_FILE"

echo -e "${GREEN}Starting performance analysis...${NC}"

for N in "${N_VALUES[@]}"; do
    echo -e "\n${BLUE}Testing with N = $N${NC}"
    
    # Run serial version multiple times
    echo "Running serial version..."
    SERIAL_TIMES=()
    for run in $(seq 1 $RUNS); do
        echo "  Run $run/$RUNS"
        OUTPUT=$(./serial_prime $N 2>&1)
        SERIAL_TIME=$(echo "$OUTPUT" | grep "Total execution time" | awk '{print $4}')
        SERIAL_TIMES+=($SERIAL_TIME)
        echo "    Serial time: ${SERIAL_TIME}s"
    done
    
    # Calculate average serial time
    SERIAL_AVG=$(python3 -c "times = [${SERIAL_TIMES[*]}]; print(f'{sum(times)/len(times):.6f}')")
    echo "  Average serial time: ${SERIAL_AVG}s"
    
    # Test different process counts
    for PROCS in "${PROCESS_COUNTS[@]}"; do
        echo -e "\n  ${YELLOW}Testing with $PROCS processes${NC}"
        
        MPI_TIMES=()
        for run in $(seq 1 $RUNS); do
            echo "    Run $run/$RUNS"
            OUTPUT=$(mpirun -np $PROCS ./mpi_prime $N 2>&1)
            MPI_TIME=$(echo "$OUTPUT" | grep "Total execution time" | awk '{print $4}')
            MPI_TIMES+=($MPI_TIME)
            echo "      MPI time: ${MPI_TIME}s"
        done
        
        # Calculate average MPI time
        MPI_AVG=$(python3 -c "times = [${MPI_TIMES[*]}]; print(f'{sum(times)/len(times):.6f}')")
        SPEEDUP=$(python3 -c "print(f'{$SERIAL_AVG/$MPI_AVG:.3f}')")
        EFFICIENCY=$(python3 -c "print(f'{($SERIAL_AVG/$MPI_AVG)/$PROCS*100:.1f}')")
        
        echo "    Average MPI time: ${MPI_AVG}s"
        echo "    Speedup: ${SPEEDUP}x"
        echo "    Efficiency: ${EFFICIENCY}%"
        
        # Save individual run results
        for i in $(seq 0 $((RUNS-1))); do
            RUN_SPEEDUP=$(python3 -c "print(f'{$SERIAL_AVG/${MPI_TIMES[i]}:.6f}')")
            RUN_EFFICIENCY=$(python3 -c "print(f'{($SERIAL_AVG/${MPI_TIMES[i]})/$PROCS*100:.2f}')")
            echo "$N,$PROCS,$((i+1)),$SERIAL_AVG,${MPI_TIMES[i]},$RUN_SPEEDUP,$RUN_EFFICIENCY" >> "$RESULTS_FILE"
        done
    done
done

echo -e "\n${GREEN}Performance analysis completed!${NC}"
echo "Results saved to: $RESULTS_FILE"

# Generate Python script for plotting results
cat > "$RESULTS_DIR/plot_results.py" << 'EOF'
#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read results
df = pd.read_csv('performance_results.csv')

# Calculate averages
avg_df = df.groupby(['N', 'Processes']).agg({
    'Serial_Time': 'mean',
    'MPI_Time': 'mean',
    'Speedup': 'mean',
    'Efficiency': 'mean'
}).reset_index()

# Create plots
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 12))
fig.suptitle('MPI Prime Search Performance Analysis', fontsize=16)

# Plot 1: Execution Time vs Process Count
for n in avg_df['N'].unique():
    n_data = avg_df[avg_df['N'] == n]
    ax1.plot(n_data['Processes'], n_data['MPI_Time'], 'o-', label=f'N={n:,}')
ax1.set_xlabel('Number of Processes')
ax1.set_ylabel('Execution Time (seconds)')
ax1.set_title('Execution Time vs Process Count')
ax1.legend()
ax1.grid(True)

# Plot 2: Speedup vs Process Count
for n in avg_df['N'].unique():
    n_data = avg_df[avg_df['N'] == n]
    ax2.plot(n_data['Processes'], n_data['Speedup'], 'o-', label=f'N={n:,}')
# Add ideal speedup line
max_procs = avg_df['Processes'].max()
ax2.plot(range(1, max_procs+1), range(1, max_procs+1), 'k--', label='Ideal')
ax2.set_xlabel('Number of Processes')
ax2.set_ylabel('Speedup')
ax2.set_title('Speedup vs Process Count')
ax2.legend()
ax2.grid(True)

# Plot 3: Efficiency vs Process Count
for n in avg_df['N'].unique():
    n_data = avg_df[avg_df['N'] == n]
    ax3.plot(n_data['Processes'], n_data['Efficiency'], 'o-', label=f'N={n:,}')
ax3.axhline(y=100, color='k', linestyle='--', label='100% Efficiency')
ax3.set_xlabel('Number of Processes')
ax3.set_ylabel('Efficiency (%)')
ax3.set_title('Efficiency vs Process Count')
ax3.legend()
ax3.grid(True)

# Plot 4: Scalability Analysis
for n in avg_df['N'].unique():
    n_data = avg_df[avg_df['N'] == n]
    serial_time = n_data[n_data['Processes'] == 1]['Serial_Time'].iloc[0]
    normalized_time = n_data['MPI_Time'] / serial_time
    ax4.plot(n_data['Processes'], normalized_time, 'o-', label=f'N={n:,}')
ax4.set_xlabel('Number of Processes')
ax4.set_ylabel('Normalized Execution Time')
ax4.set_title('Scalability Analysis (Lower is Better)')
ax4.legend()
ax4.grid(True)

plt.tight_layout()
plt.savefig('performance_analysis.png', dpi=300, bbox_inches='tight')
print("Plots saved to performance_analysis.png")

# Print summary statistics
print("\n=== PERFORMANCE SUMMARY ===")
for n in sorted(avg_df['N'].unique()):
    print(f"\nN = {n:,}:")
    n_data = avg_df[avg_df['N'] == n]
    for _, row in n_data.iterrows():
        print(f"  {row['Processes']} processes: {row['Speedup']:.2f}x speedup, {row['Efficiency']:.1f}% efficiency")
    
    # Find best configuration
    best_speedup = n_data.loc[n_data['Speedup'].idxmax()]
    print(f"  Best speedup: {best_speedup['Speedup']:.2f}x with {best_speedup['Processes']} processes")
EOF

chmod +x "$RESULTS_DIR/plot_results.py"

echo -e "\nTo generate plots and analysis:"
echo -e "${YELLOW}cd $RESULTS_DIR && python3 plot_results.py${NC}"

echo -e "\n${BLUE}Analysis script completed!${NC}"
