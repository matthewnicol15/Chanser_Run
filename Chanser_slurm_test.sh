#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=3000
#SBATCH --job-name=Chanser_Test
#SBATCH --partition=production
#SBATCH --account=clas12
chanser_proof 10 /home/matthewn/Documents/Macros/Chanser_Run/finalstates/Scaling_Strangeness/Processor.C
