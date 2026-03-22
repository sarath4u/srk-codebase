#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){

int np, rank;
const int root = 0;
int data[4], mine, i;
int sendcnt, recvcnt;
sendcnt = 1;
recvcnt = 1;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
mine = 10 * rank;
printf("data before gather in rank [%d ]:%d\n", rank, mine);
MPI_Gather(&mine, sendcnt, MPI_INT, data, recvcnt, MPI_INT, root, MPI_COMM_WORLD);
if (rank == root){
	printf("data after gather: \n");
	for (i = 0; i < 4; i++)
		printf("%d\t", data[i]);
	}
MPI_Finalize();
}
