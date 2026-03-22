#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank, data;
MPI_Request request;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
if (rank == 0){
	data = 50;
	printf("Sending data: %d, My rank: %d\n", data, rank);
	MPI_Isend(&data, 1, MPI_INT, 1, 123, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status);
	};
if (rank == 1){
	MPI_Recv(&data, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Receiving data: %d, My rank: %d\n", data, rank);
	};
MPI_Finalize();
}
