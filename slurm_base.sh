#!/bin/bash
#SBATCH --job-name=T2
#SBATCH --output=output_%j.txt
#SBATCH --error=error_%j.txt
#SBATCH --ntasks=5
#SBATCH --cpus-per-task=8
#SBATCH --time=0-00:30
#SBATCH --partition=all

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
gcc -o script script_base.c
./script
