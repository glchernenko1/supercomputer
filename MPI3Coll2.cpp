#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double arr[5];
	if (rank == 0) 
		for (int i = 0; i < 5; i++)
			pt >> arr[i];
	MPI_Bcast(arr, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (rank > 0) 
		for (int i = 0; i < 5; i++)
			pt << arr[i];
			
}
