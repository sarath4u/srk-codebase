#include <stdio.h>
#include <mpi.h>

main(int argc, char *argv[])
{
int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int size, rank;
const int root = 0;
int search = 6, result = -1, i;
int flag = 0, indx = -1;
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

MPI_Scatter(arr, sendcnt, MPI_INT, recvbuff, recvcnt, MPI_INT, root, MPI_COMM_WORLD);
for (i = 0; i < sendcnt ; i++){
	if (recvbuff[i] == search){
		indx = i + sendcnt * rank;
		break;
		}
	};
MPI_Reduce(&indx, &result, 1, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);
if (rank == root)
	printf("rank = %d; index = %d; \n", rank, result);
MPI_Finalize();
};
