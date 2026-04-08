#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    long long steps = 100000000;
    double step = 1.0 / (double)steps;
    double local_sum = 0.0;
    double global_sum = 0.0;
    
    double start_time = MPI_Wtime();
    
    // Distribute work
    for (long long i = rank; i < steps; i += size) {
        double x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }
    
    // Combine results
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    double end_time = MPI_Wtime();
    
    if (rank == 0) {
        double pi = global_sum * step;
        printf("Pi = %.15f\n", pi);
        printf("Error = %.15f\n", fabs(pi - M_PI));
        printf("Time = %.4f seconds\n", end_time - start_time);
        printf("Processes = %d\n", size);
    }
    
    MPI_Finalize();
    return 0;
}




# Compile
mpicc mpi_pi.c -o mpi_pi

# Run with 4 processes
mpirun -np 4 ./mpi_pi
