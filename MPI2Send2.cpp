#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double nbuf;
	int s;
	MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &s);
	int bufsize = size * MPI_BSEND_OVERHEAD + size * s;
	char* buf = (char*)malloc(bufsize);
	MPI_Buffer_attach(buf, bufsize);

	if (rank == 0) {
		double ans;
		MPI_Status stat;
		for (int i = size - 1; i > 0; i--) {
			MPI_Recv(&ans, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &stat);
			pt << ans;
		}
	}
	else {
		double in;
		pt >> in;
		nbuf = in;
		MPI_Bsend(&nbuf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
}
