#!/bin/bash

#SBATCH --job-name=MPI_Basics
#SBATCH --nodes=4
#SBATCH -p scavenge
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=1G
#SBATCH --time=00:01:00
#SBATCH --mail-user=ncm5@rice.edu
#SBATCH --mail-type=all

srun ./point
