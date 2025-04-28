#!/bin/bash

#SBATCH --partition=lva            # Partition für den Job (je nach Cluster ggf. anpassen)
#SBATCH --job-name=montecarlo      # Name des Jobs
#SBATCH --output=output.log        # Ausgabe in die Logdatei
#SBATCH --ntasks=1                 # Nur ein Prozess
#SBATCH --cpus-per-task=12         # Anzahl der CPUs für OpenMP (nicht --ntasks-per-node)
#SBATCH --exclusive                # Exklusive Nutzung des Knotens
#SBATCH --time=00:30:00            # Maximale Laufzeit (z. B. 30 Minuten)

# Info-Ausgabe
echo "Benchmark on $(hostname) at $(date)"
N=700000000

# Wenn dein Programm N als Argument erwartet, kannst du es hier übergeben
# Wenn N im Code fest ist, kannst du diese Variable ignorieren oder später zum Kompilieren nutzen

# Threadanzahlen zum Testen (für später kannst du 1, 4, 8, 12 nehmen)
for t in 12; do
    export OMP_NUM_THREADS=$t

    echo ""
    echo "Running with $t threads:"


    /usr/bin/time -f "Real time reduction: %e seconds" ./reduction
    /usr/bin/time -f "Real time atomic: %e seconds" ./atomic
    /usr/bin/time -f "Real time critical: %e seconds" ./critical

done

echo "Done at $(date)"
