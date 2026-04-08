#include <omp.h>
#include <stdio.h>
#include <math.h>

int main() {
    long long steps = 100000000;
    double step = 1.0 / (double)steps;
    double pi = 0.0;
    
    double start = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:pi)
    for (long long i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }
    
    pi *= step;
    double end = omp_get_wtime();
    
    printf("Pi = %.15f\n", pi);
    printf("Error = %.15f\n", fabs(pi - M_PI));
    printf("Time = %.4f seconds\n", end - start);
    printf("Threads = %d\n", omp_get_max_threads());
    
    return 0;
}
/* 
 *gcc -fopenmp openmp_pi.c -o openmp_pi

# Run with 4 threads
export OMP_NUM_THREADS=4
./openmp_pi
 *
 * */
