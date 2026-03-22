#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank;
const int root = 0;
int sendbuff[3], recvbuff[3], i;
int sendcnt, recvcnt;
sendcnt = 1;
recvcnt = 1;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np); // size = 3
for (i = 0; i < np; i++){
	sendbuff[i] = rank * 300 + i * 100;
	};
printf("My rank = %d and my value = %d\t%d\t%d\n", rank, sendbuff[0], sendbuff[1], sendbuff[2]);
MPI_Alltoall(sendbuff, sendcnt, MPI_INT, recvbuff, recvcnt, MPI_INT, MPI_COMM_WORLD);
printf("My rank = %d and my value = %d\t%d\t%d\n", rank, recvbuff[0], recvbuff[1], recvbuff[2]);
MPI_Finalize();
}
