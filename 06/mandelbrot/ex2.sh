#!/bin/bash

#SBATCH --partition=lva            # Partition für den Job (je nach Cluster ggf. anpassen)
#SBATCH --job-name=montecarlo      # Name des Jobs
#SBATCH --output=output.log        # Ausgabe in die Logdatei
#SBATCH --ntasks=1                 # Nur ein Prozess
#SBATCH --cpus-per-task=12         # Anzahl der CPUs für OpenMP (nicht --ntasks-per-node)
#SBATCH --exclusive                # Exklusive Nutzung des Knotens
#SBATCH --time=00:30:00            # Maximale Laufzeit (z. B. 30 Minuten)

for t in 1 2 4 8 12; do
    export OMP_NUM_THREADS=$t

    echo ""
    echo "Running with $t threads:"


    /usr/bin/time -f "mandelbrot: " ./mandelbrot

done