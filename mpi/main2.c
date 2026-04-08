#include <mpi.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	char message[50];
	if(rank == 0) {
		strcpy(message, "Hello from root process");
	}

	MPI_Bcast(message, 50, MPI_CHAR, 0, MPI_COMM_WORLD);

	printf("Process %d has received the message %s\n", rank, message);

	MPI_Finalize();
}
