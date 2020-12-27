#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI2Send13");
	int flag; MPI_Status status;
	int in; int i = 1;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	
	int rank, size;
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		pt >> in;
		MPI_Send(&in, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&in, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		pt << in;
	}
	else 
	{
		int send; int recv;

		pt >> send;
		
		if (rank == 1) {
			MPI_Ssend(&send, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD);
			MPI_Recv(&recv, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			pt << recv;
		}
		else
			if (rank == (size - 1)) {
				MPI_Recv(&recv, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Ssend(&send, 1, MPI_INT, size - 2, 1, MPI_COMM_WORLD);
				pt << recv;
			}
			else
			{
				MPI_Ssend(&send, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD);
				MPI_Recv(&recv, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				pt << recv;
			}
	}
}
