#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double tmp, ans;
	int n;
	pt >> tmp >> n;
	if (n == rank)
		pt << tmp << n;
	else
	{
		MPI_Send(&tmp, 1, MPI_DOUBLE, n, 0, MPI_COMM_WORLD);
		MPI_Status stat;
		MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &stat);
		MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &stat);
		pt << ans<< stat.MPI_SOURCE;
	}

}
