#include "pt4.h"
#include "mpi.h"
#include <vector>
using namespace std;

void Solve()
{
    Task("MPI3Coll7");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double ans[3];
	vector < double> buf(3*size);
	if (rank == 0) 
		for (int i = 0; i < 3*size; i++) 
			pt >> buf[i];		
	MPI_Scatter(buf.data(), 3, MPI_DOUBLE, ans, 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	pt << ans[0]<< ans[1] << ans[2];
}
