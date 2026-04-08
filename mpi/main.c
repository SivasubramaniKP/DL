#include <stdio.h>
#include <mpi.h>

int main ( int argc, char **argv ) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("RANK %d SIZE %d", rank, size);

	if(size > 1) {

		if(rank == 0) {
			int number = 67;
			MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			printf("Process 0 has sent the message %d to Process 1", number);
		}

		if (rank == 1) {
			int result;
			MPI_Recv(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process 0 has sent me %d", result);
				
		}
	}

	MPI_Finalize();
		
	return 0;
}

