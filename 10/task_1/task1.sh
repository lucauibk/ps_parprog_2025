#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name 10_task_1
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

module load gcc/12.2.0

N = 500000000
export OMP_NUM_THREADS=6
export OMP_PLACES=cores
export OMP_PROC_BIND=spread

echo "Running task 1 with OMP_NUM_THREADS=6, OMP_PLACES=cores, and OMP_PROC_BIND=spread"
./task1 $N

export OMP_PROC_BIND=close
export OMP_PLACES="{0},{1},{2},{3},{4},{5}"
echo "Running task 1 with OMP_PROC_BIND=close and OMP_PLACES set"
./task1 $N