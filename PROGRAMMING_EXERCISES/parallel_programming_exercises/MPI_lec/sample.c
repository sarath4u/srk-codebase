#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
printf("No of Processes: %d, My rank: %d\n", np, rank);
MPI_Finalize();
}
