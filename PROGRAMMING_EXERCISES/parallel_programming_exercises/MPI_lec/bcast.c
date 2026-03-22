#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank, data;
const int root = 0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
if (rank == 0){
	data = 1000;
	};
MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
printf("Rank [%d]: data: %d\n", rank, data);
MPI_Finalize();
}
