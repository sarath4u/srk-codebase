#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
if (rank == 0){
int data = 50;
printf("Sending data: %d, My rank: %d\n", data, rank);
MPI_Send(&data, 1, MPI_INT, 1, 123, MPI_COMM_WORLD);
};
if (rank == 1){
int data;
MPI_Recv(&data, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("Receiving data: %d, My rank: %d\n", data, rank);
};
MPI_Finalize();
}
