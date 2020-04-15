# MPI-Basics

1. `$ source setup.sh` to load the necessary MPI compliler and library.
2. `$ make` to complile the examples.
3. Edit `myjob.slurm` to have your email and the name of the example you want to run.
4. `$ sbatch myjob.slurm` to submit your job request.
5. `$ squeue -u <your net id>` to see the status of your active or pending jobs.
