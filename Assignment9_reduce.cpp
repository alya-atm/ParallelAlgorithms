#include <iostream>
#include "mpi.h"
#include <math.h>
using namespace std;
int main(int argc, char **argv)
{
    int rank, size, to_sent;
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int N=1000000;
    int* arr;
    arr = new int[N];
    for(int i=0; i<N; i++)
        arr[i]=1;
    int local_sum = 0;
    for (int i = 0; i < N; i++) local_sum += arr[i];
    start_time = MPI_Wtime();
    int total_sum=0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        end_time = MPI_Wtime();
        cout<<"Total sum: "<<total_sum-local_sum<<", Time: "<<end_time-start_time<<endl;
}
    MPI_Finalize();
    return 0;
}