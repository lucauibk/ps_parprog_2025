#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name vectorization_test
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

echo "Compiling..."
make

echo -e "\nRunning baseline:"
./vec_baseline $SIZE $REPS

echo -e "\nRunning auto_vectorized:"
./auto_vectorized $SIZE $REPS

echo -e "\nMeasuring with perf (SSE Single Precision):"
echo -e "\nBaseline:"
perf stat -e r4010 ./vec_baseline $SIZE $REPS

echo -e "\nAuto-vectorized:"
perf stat -e r4010 ./auto_vectorized $SIZE $REPS
