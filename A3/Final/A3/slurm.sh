#!/bin/bash

####### set memory that nodes provide (check CCR documentation, e.g., 32GB)
#SBATCH --mem=32000

####### make sure no other jobs are assigned to your nodes
#SBATCH --exclusive

####### further customizations
#SBATCH --job-name="a3"
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --gres=gpu:tesla_v100-pcie-16gb:1

module load cuda

./a3 100000000 0.0001
./a3 100000000 0.0001
./a3 100000000 0.0001
./a3 1000000000 0.0001
./a3 1000000000 0.0001
./a3 1000000000 0.0001
./a3 10000000000 0.0001
./a3 10000000000 0.0001
./a3 10000000000 0.0001
./a3 100000000000 0.0001
./a3 100000000000 0.0001
./a3 100000000000 0.0001
