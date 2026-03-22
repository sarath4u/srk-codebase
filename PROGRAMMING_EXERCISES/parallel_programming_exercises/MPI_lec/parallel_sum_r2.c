#include <stdio.h>
#include <mpi.h>

int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int dump[10]; // Temperory array for slaves
int n = 10; // size of the array
main(int argc, char *argv[])
{
	int size, rank, j, part_sum = 0, sum;
	const int root = 0;
	int elements_per_process, elements_recvd;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Request request;
	MPI_Status status;

	if (rank == root){
		int i, index;
		elements_per_process = n / size;
		for (i = 0; i < elements_per_process; i++)
			part_sum += arr[i];
		for (i = 1; i < size-1; i++){
			int index = i * elements_per_process;
			MPI_Send(&elements_per_process, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
			MPI_Send(&arr[index], elements_per_process, MPI_INT, i, 123, MPI_COMM_WORLD);
		}
		index = elements_per_process * i;
		int elements_left = n - index;
		MPI_Send(&elements_left, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
		MPI_Send(&arr[index], elements_left, MPI_INT, i, 123, MPI_COMM_WORLD);
//	printf("Partial sum on rank %d: %d\n", rank, part_sum);
	}
	else {
		int i;
		MPI_Recv(&elements_recvd, 1, MPI_INT, root, 123, MPI_COMM_WORLD, &status);
		MPI_Recv(&dump, elements_recvd, MPI_INT, root, 123, MPI_COMM_WORLD, &status);
		for (i = 0; i < elements_recvd; i++)
			part_sum += dump[i];
//		printf("Partial sum on rank %d: %d\n", rank, part_sum);
	}
	int i;
	for (j = size; size > 2; size -= 2){
		for (i = 1; i < j; i += 2){
			printf("%d, %d\n", i, i-1);
//			MPI_Send(&part_sum, 1, MPI_INT, i-1, 123, MPI_COMM_WORLD);
//			printf("Sending sum %d from rank %d\n", part_sum, i-1);
//			MPI_Recv(&sum, 1, MPI_INT, i-1, 123, MPI_COMM_WORLD, &status);
//			printf("Receiving sum %d from rank %d\n", sum, i-1);
		}
	}
	MPI_Finalize();
}
