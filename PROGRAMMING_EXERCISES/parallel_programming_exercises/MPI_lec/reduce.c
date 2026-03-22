#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank;
const int root = 0;
int data, mine;
int sendcnt, recvcnt;
sendcnt = 1;
recvcnt = 1;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
mine = 10 - rank;
printf("data before reduction in rank [%d ]:%d\n", rank, mine);
MPI_Reduce(&mine, &data, recvcnt, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
if (rank == root){
	printf("data after reduction: %d\n", data);
	}
MPI_Finalize();
}
