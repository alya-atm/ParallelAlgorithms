#include <stdio.h>
#include "mpi.h"

#define n 1000


using namespace std;

void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	int i;
	for (i = 0; i < *l; i++)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}

void max_fun(void*a, void*b, int*l, MPI_Datatype *type){
	for(int i = 0; i < *l; i++)
	    ((int*)b)[i] = max(((int*)a)[i], ((int*)b)[i]);}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b1[n] = {0};
    int b2[n] = {0};
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++) {
	     a[i] = i + rank + 1;}
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&max_fun, 1, &op);
	MPI_Reduce(a, b1, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Reduce(a, b2, n, MPI_INT, MPI_MAX , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0) 
	cout <<"Own function for finding max value - "<< b1[0] << ", MPI_MAX - " << b2[0]<<endl;
	MPI_Finalize();
}