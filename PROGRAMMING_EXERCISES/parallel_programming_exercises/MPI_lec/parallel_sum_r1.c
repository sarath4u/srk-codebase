#include <stdio.h>
#include <mpi.h>

int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int dump[10]; // Temperory array for slaves
int n = 10; // size of the array
main(int argc, char *argv[])
{
	int size, rank;
	const int root = 0;
	int elements_per_process, elements_recvd;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Request request;
	MPI_Status status;
	
	if (rank == root){
		int indx, i;
		elements_per_process = n / size;
		if (size > 1) {
			for (i = 1; i < size - 1; i++){
				indx = elements_per_process * i;
				MPI_Send(&elements_per_process, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
				MPI_Send(&arr[indx], elements_per_process, MPI_INT, i, 123, MPI_COMM_WORLD);
				}
			indx = elements_per_process * i;
			int elements_left = n - indx;
			MPI_Send(&elements_left, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
			MPI_Send(&arr[indx], elements_left, MPI_INT, i, 123, MPI_COMM_WORLD);
			}
		int sum = 0;
		for (i = 0; i < elements_per_process; i++)
			sum += arr[i];
		printf("Partial sum = %d\n", sum);
		int temp;
		for (i = 1; i < size; i++){
			MPI_Recv(&temp, 1, MPI_INT, i, 123, MPI_COMM_WORLD, &status);
			int sender = status.MPI_SOURCE;
			sum += temp;
			}
		printf("Total sum = %d\n", sum);
		}
	else {
		MPI_Recv(&elements_recvd, 1, MPI_INT, root, 123, MPI_COMM_WORLD, &status);
		MPI_Recv(&dump, elements_recvd, MPI_INT, root, 123, MPI_COMM_WORLD, &status);
		int i, partial_sum = 0;
		for (i = 0; i < elements_recvd; i++)
			partial_sum += dump[i];
		printf("Partial sum = %d\n", partial_sum);
		MPI_Send(&partial_sum, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
	}
	MPI_Finalize();
};
