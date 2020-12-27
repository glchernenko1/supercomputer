#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send9");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank != 0) {
		int n;
		pt >> n;
		if (n!=0) {
			double bufSend[30];
			for (int i = 0; i < n; i++)
				pt >> bufSend[i];
			MPI_Send(&bufSend, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
	}
	else {
		double bufrec[30];
		int count;
		MPI_Status s;
		MPI_Recv(&bufrec, 30, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &s);
		MPI_Get_count(&s, MPI_DOUBLE, &count);
		for (int i = 0; i < count; i++)
			pt << bufrec[i];
		pt << s.MPI_SOURCE;
	}

}
