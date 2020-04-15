#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main() {
    int provided;
    MPI_Init_thread(0, 0, MPI_THREAD_FUNNELED, &provided);

    int my_rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int threads = omp_get_max_threads();

#pragma omp parallel
    {
        int curr_thread = omp_get_thread_num();
        printf("Node %d / %d : Thread %d / %d\n", my_rank, world_size, curr_thread, threads);
    }

    MPI_Finalize();

    return 0;
}