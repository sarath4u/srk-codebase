#include <stdio.h>
#include <mpi.h>

main(int argc, char *argv[])
{
int size, rank;
const int root = 0;
int result = 0, sum, i;
int sendcnt, recvcnt;
int localstrt, localend;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Request request;
MPI_Status status;
sendcnt = 10 / size;
recvcnt = 10 / size;
int recvbuff[sendcnt];
int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
MPI_Scatter(arr, sendcnt, MPI_INT, recvbuff, recvcnt, MPI_INT, root, MPI_COMM_WORLD);
for (i = 0; i < sendcnt ; i++){
	sum += recvbuff[i];
	MPI_Barrier(MPI_COMM_WORLD);
	}
MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
if (rank == root)
	printf("rank = %d; sum = %d; \n", rank, result);
MPI_Finalize();
};
