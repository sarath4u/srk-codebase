#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank, send_data, recv_data;
MPI_Request request;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
if (rank == 0){
	send_data = 50;
	MPI_Sendrecv(&send_data, 1, MPI_INT, 1, 123, &recv_data, 1, MPI_INT, 1, 456, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Sending data: %d and receiving data: %d. My rank: %d\n", send_data, recv_data, rank);
	};
if (rank == 1){
	send_data = 100;
	MPI_Sendrecv(&send_data, 1, MPI_INT, 0, 456, &recv_data, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Sending data: %d and receiving data: %d. My rank: %d\n", send_data, recv_data, rank);
	};
MPI_Finalize();
}
