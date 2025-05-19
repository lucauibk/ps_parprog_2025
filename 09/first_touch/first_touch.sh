#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name=first_touch
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive

# Define thread counts in an array (fix: = causes syntax error when not used properly)
export OMP_NUM_THREADS=12
export GOMP_CPU_AFFINITY="0-11"
N=40000

echo "Running"
./first_touch $N
