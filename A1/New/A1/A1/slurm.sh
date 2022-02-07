#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=faculty
#SBATCH --partition=planex
#SBATCH --qos=planex
#SBATCH --account=cse570f21
#SBATCH --exclusive
#SBATCH --mem=64000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="CSE570_A1_Sort"
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=16
#SBATCH --time=01:00:00

module load gcc
module load intel-mpi/2019.5
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

srun --mpi=pmi2 ./a1 100000
srun --mpi=pmi2 ./a1 10000000
srun --mpi=pmi2 ./a1 1000000000
