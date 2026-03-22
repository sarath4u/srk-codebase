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
	MPI_Send(&data, 1, MPI_INT, 1, 123, MPI_COMM_WORLD);
	};
if (rank == 1){
	MPI_Irecv(&data, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status); // comment this line to see the difference                                  
	printf("Receiving data: %d, My rank: %d\n", data, rank);
	};
MPI_Finalize();
}
