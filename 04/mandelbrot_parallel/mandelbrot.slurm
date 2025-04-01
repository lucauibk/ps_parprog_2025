#!/bin/bash
#SBATCH --partition=lva
#SBATCH --job-name=mandelbrot_parallel
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1  # Maximale Anzahl an CPU-Kernen (passt sich an)
#SBATCH --exclusive

# Output-Datei
OUTPUT_FILE="benchmark_results.txt"
echo "Mandelbrot Benchmark Ergebnisse" > $OUTPUT_FILE
echo "=================================" >> $OUTPUT_FILE

# Liste der Threads für den Test
THREADS=(1 2 4 8 12)

echo "Starte Benchmark..."
for T in "${THREADS[@]}"; do
    echo ""
    echo "Running with $T threads..."
    echo "Running with $T threads..." >> $OUTPUT_FILE

    # Startzeit erfassen
    START_TIME=$(date +%s.%N)

    # Programm mit entsprechender Anzahl an Threads ausführen
    srun --cpus-per-task=$T ./mandelbrot "$T"


    # Endzeit erfassen
    END_TIME=$(date +%s.%N) 

    # Dauer berechnen
    DURATION=$(echo "$END_TIME - $START_TIME" | bc)


    echo "Execution Time: $DURATION seconds" >> $OUTPUT_FILE
    echo "Execution Time: $DURATION seconds"
done

echo "Benchmark abgeschlossen. Ergebnisse in $OUTPUT_FILE gespeichert."