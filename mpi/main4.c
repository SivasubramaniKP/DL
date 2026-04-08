#include <mpi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	int next = (rank + 1) % size;
	int prev = (rank - 1 + size) % size;

	char msg[1000];
	char temp[1000];
	sprintf(msg, "THIS IS A MESSAGE FROM PROCESS %d and sending it to %d\n", rank, next);

	MPI_Sendrecv(msg, 1000, MPI_CHAR, next, 0,
			temp, 1000, MPI_CHAR, prev, 0,

			MPI_COMM_WORLD, MPI_STATUS_IGNORE
			);
	printf("%s\n\n", temp);

	MPI_Finalize();
}
