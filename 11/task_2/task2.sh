#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name vec_omp
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

SIZE=2048
REPS=1000000

echo "Benchmarking OpenMP SIMD version"
echo

if [[ ! -x simd ]]; then
    echo "Executable simd not found! Run 'make' first."
    exit 1
fi

perf stat ./simd $SIZE $REPS

