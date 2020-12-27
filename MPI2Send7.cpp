#include "pt4.h"
#include "mpi.h"

using namespace std;
void Solve()
{
    Task("MPI2Send7");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		int n;
		pt >> n;
		double *arr = new double[n];
		for (int i = 0; i < n; i++) 
			pt >> arr[i];

		double out;
		for (int i = 1; i < size-1; i++) {
			out = arr[i-1];
			MPI_Send(&out, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
		}

		double out2[9];
		for (int i = size - 1; i <= n; i++)
			out2[i - size + 1] = arr[i - 1];

		delete arr;
		MPI_Send(&out2, n - size + 2, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD);
	}
	else {
		if (rank == size - 1) {
			double buf[9];
			MPI_Status s;
			int n;
			MPI_Recv(&buf, 9, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &s);
			MPI_Get_count(&s, MPI_DOUBLE, &n);
			for (int i = 0; i < n; i++) 
				pt << buf[i];
		}
		else {
			double one;
			MPI_Status s;
			MPI_Recv(&one, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &s);
			pt << one;
		}
	}
}
