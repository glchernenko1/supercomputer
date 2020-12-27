#include "pt4.h"
#include "mpi.h"
#include <vector>

using namespace std;

double sum(int N) {
	double sum = 0;
	double tmp;
	for (int i = 0; i < N; ++i) {
		pt >> tmp;
		sum += tmp;
	}
	return sum;
}






void Solve()
{
    Task("MPI1Proc8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int n;
	pt >> n;
	if (rank % 2 == 0)
		pt << sum(n);
	else
		pt << sum(n) / n;
}
