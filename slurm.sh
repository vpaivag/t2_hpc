#!/bin/bash
#SBATCH --job-name=T2
#SBATCH --output=output_%j.txt
#SBATCH --error=error_%j.txt
#SBATCH --ntasks=5
#SBATCH --cpus-per-task=8
#SBATCH --time=0-00:10
#SBATCH --partition=all


# Array of source files for the different versions of adder
versions=("script_v1.c" "script_v2.c" "script_v3.c")

# Loop through each version, compile, and run
for version in "${versions[@]}"; do

  name=$(basename "$version" .c)
  
  # Compile the current version
  gcc -o "$name" "$version" -fopenmp
  
  # Run the compiled binary
  echo "Running $name..."
  ./"$name"

  echo 
done