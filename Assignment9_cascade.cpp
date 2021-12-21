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
    if (rank != 0)
    {
        for(int i=1; i <= (size-1)/2 ; i++)
        {
            if(rank%(2*i) == 0)
            {
                int sum_i;
                MPI_Recv(&sum_i, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD, &status);
                local_sum += sum_i;
            }
            else
            {

                MPI_Send(&local_sum, 1, MPI_INT, rank + (pow(2, i-1)), 0, MPI_COMM_WORLD);
                break;
            }
        }
    }
if(rank == size-1){
    MPI_Send(&local_sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
}
if (rank == 0)
{
    int sum_i = 0;
    MPI_Recv(&sum_i, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    local_sum = sum_i;
    end_time = MPI_Wtime();
    cout<<"Total sum : " << local_sum << ", Time : " << (end_time - start_time) <<endl;
}
MPI_Finalize();
return 0;
}