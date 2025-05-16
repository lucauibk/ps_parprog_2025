#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name=ex1
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive

# Define thread counts in an array (fix: = causes syntax error when not used properly)
THREADS=(1 2 4 8 12)
N=1500


for i in "${THREADS[@]}"
do
  echo "Running with $i threads"
  export OMP_NUM_THREADS=$i

  echo "version 1:"
  ./ex1 $N

  echo "version 2:"
  ./ex1_fixed $N

  echo "-----------------------------------"
done
