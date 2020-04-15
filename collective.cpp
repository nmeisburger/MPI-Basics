#include <mpi.h>
#include <stdio.h>

#define SEND_SIZE 4

int main() {

    // Initialize MPI.
    MPI_Init(0, 0);

    // Determine MPI process id and the number of processes.
    int my_rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // For storing messages from other nodes.
    int *gather_buf = new int[SEND_SIZE * world_size];

    // Stores message to send to other nodes.
    int *send_buf = new int[SEND_SIZE];

    // Initialize message to send.
    for (int i = 0; i < SEND_SIZE; i++) {
        send_buf[i] = i * my_rank;
    }

    // Gather will receive a message from every node in the destination node.
    MPI_Gather(send_buf, SEND_SIZE, MPI_INT, gather_buf, SEND_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Print our results in the destination node.
    if (my_rank == 0) {
        printf("Received from Gather: ");
        for (int i = 0; i < world_size * SEND_SIZE; i++) {
            printf("%d ", gather_buf[i]);
        }
        printf("\n");
    }

    // The number of items to send to each node.
    int counts[4] = {3, 4, 2, 5};

    // The offsets of each nodes section within the array.
    int offsets[4] = {0, 3, 7, 9};

    // The data to send.
    int *data;

    // For receiving the data;
    int *received = new int[counts[my_rank]];

    // Initialize the data in the sending node.
    if (my_rank == 0) {
        // The data to send to other nodes.
        data = new int[14];
        for (int i = 0; i < 14; i++) {
            data[i] = -i;
        }
    }

    // Sends a variable sized message to every process from node 0.
    MPI_Scatterv(data, counts, offsets, MPI_INT, received, counts[my_rank], MPI_INT, 0,
                 MPI_COMM_WORLD);

    // Print what was sent.
    if (my_rank == 0) {
        for (int n = 0; n < world_size; n++) {
            printf("Sent to node %d: ", n);
            for (int j = offsets[n]; j < offsets[n] + counts[n]; j++) {
                printf("%d ", data[j]);
            }
            printf("\n");
        }
    }

    // Waits for all processes.
    MPI_Barrier(MPI_COMM_WORLD);

    // Print what was received.
    for (int i = 0; i < world_size; i++) {
        if (my_rank == i) {
            printf("Received in node %d: ", i);
            for (int j = 0; j < counts[i]; j++) {
                printf("%d ", received[j]);
            }
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}
