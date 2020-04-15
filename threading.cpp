#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main() {

    // Initialize MPI.
    int provided;
    MPI_Init_thread(0, 0, MPI_THREAD_FUNNELED, &provided);

    // Determine MPI process id and the number of processes.
    int my_rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Get number of available threads.
    int threads = omp_get_max_threads();

// Foreach thread:
#pragma omp parallel
    {
        // Get thread number.
        int curr_thread = omp_get_thread_num();
        // Print process number and thread number.
        printf("Node %d / %d : Thread %d / %d\n", my_rank, world_size, curr_thread, threads);
    }

    MPI_Finalize();

    return 0;
}