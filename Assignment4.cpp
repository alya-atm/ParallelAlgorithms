#include <stdio.h>
#include <iostream>
#include <mpi.h>
#define NTIMES 100
using namespace std;
int main(int argc, char* argv[]) {
	double time_start, time_finish;
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	time_start = MPI_Wtime();{
	if (rank == 1)
	{
		//cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n/2; i++) {
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
			         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		//	cout << "Hello from process " << message << endl;
		}
	}
	else if (rank % 2 ==1)
	MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	time_finish = MPI_Wtime();
	cout << "process " << rank << "time = " << (time_finish - time_start) / NTIMES << endl;
	MPI_Finalize();
	return 0;
}