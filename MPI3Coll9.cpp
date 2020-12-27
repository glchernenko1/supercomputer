#include "pt4.h"
#include "mpi.h"
#include <vector>
void Solve()
{
    Task("MPI3Coll9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int ans[30];
	std::vector <int> buf(int( (3 + size)*size/2));
	if (rank == 0)
		for (int i = 0; i < int((3 + size)*size / 2); i++)
			pt >> buf[i];
	Show(rank + 2);
	MPI_Scatter(buf.data(), rank+2, MPI_DOUBLE, ans, rank+2 , MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int i = 0; i < rank + 2; ++i)
		pt << ans[i];
}
