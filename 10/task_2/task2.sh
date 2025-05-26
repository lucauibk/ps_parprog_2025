#!/bin/bash

#SBATCH --partition=lva
#SBATCH --job-name=10_task_2
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive

module load gcc/12.2.0

Ns=(2 4 7 12)

for N in "${Ns[@]}"
do
    echo "### N = $N ###"

    # Sequentielle Version (1 Thread)
    export OMP_NUM_THREADS=1
    echo "--- Sequential Version (1 Thread) ---"
    ./delannoy_seq $N

    # Parallele Version mit 1 Thread
    export OMP_NUM_THREADS=1
    echo "--- Parallel Version (1 Thread) ---"
    ./delannoy_par $N

    # Parallele Version mit 12 Threads
    export OMP_NUM_THREADS=12
    export OMP_PROC_BIND=spread
    export OMP_PLACES=cores
    echo "--- Parallel Version (12 Threads) ---"
    ./delannoy_par $N

    echo ""
done
