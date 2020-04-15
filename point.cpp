#include <mpi.h>
#include <stdio.h>

int main() {

    // Initialize MPI.
    MPI_Init(0, 0);

    // Determine MPI process id and the number of processes.
    int my_rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Print rank and cluster size.
    printf("Node %d / %d\n", my_rank, world_size);

    MPI_Status status1, status2;

    if (my_rank == 0) {
        // To be executed by process 0.

        // Data to send.
        int send1[4] = {2, 4, 6, 8};
        // Buffer to use to receive data.
        float recv1[5];

        // Send and receive data.
        MPI_Send(send1, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(recv1, 5, MPI_FLOAT, 1, 2, MPI_COMM_WORLD, &status2);

        // Print data sent and received.
        printf("Sent Node 0: %d %d %d %d\n", send1[0], send1[1], send1[2], send1[3]);
        printf("Received Node 0: %f %f %f %f %f\n", recv1[0], recv1[1], recv1[2], recv1[3],
               recv1[4]);
    } else if (my_rank == 1) {
        // To be executed by process 1.

        // Buffer to use to receive data.
        int recv2[4];
        // Data to send.
        float send2[5] = {2.1, 3.3, 6.2, 8.5, 9.5};

        // Send and receive data.
        MPI_Recv(recv2, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status1);
        MPI_Send(send2, 5, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);

        // Print data sent and received.
        printf("Sent Node 1: %f %f %f %f %f\n", send2[0], send2[1], send2[2], send2[3], send2[4]);
        printf("Received Node 1: %d %d %d %d\n", recv2[0], recv2[1], recv2[2], recv2[3]);
    }

    MPI_Finalize();

    return 0;
}