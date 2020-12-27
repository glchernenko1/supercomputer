#include "pt4.h"
#include "omp.h"
#include "cmath"
#include <ctime>
#define NUM_THREADS 2

double oneStream(double x, int n)
{
	double sumTmp = 0, sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= i+n; ++j)
			sumTmp += (j + cos((x + j)))/(2 * i*j - 1);
		sum += 1 / sumTmp;
		sumTmp = 0;
	}
	return sum;
}


double multipleStream(double x, int n)
{
	omp_set_num_threads(NUM_THREADS);
	double  sum = 0;
	#pragma omp parallel  reduction  (+:sum)
	{
		double start = clock();
		double sumTmp = 0;
		int count = 0;
		#pragma omp for  nowait schedule (static, 1)
			for (int i = 1; i <= n; ++i)
			{
				for (int j = 1; j <= i + n; ++j)
				{
					sumTmp += (j + cos((x + j))) / (2 * i*j - 1);
					count++;
				}
				sum += 1 / sumTmp;
				sumTmp = 0;
			}
		auto end = clock();
		Show("Count ", count);
		ShowLine("Thread time: ", end - start);
	}
	return sum;	
}

void Solve()
{
    Task("OMPBegin18");
	int n;
	double x;
	pt >> x >> n;
	double start = clock();
	auto ans = oneStream(x, n);
	pt << ans;
	double end = clock();
	ShowLine("Single thread time: ", end - start);

	pt >> x >> n;
	omp_set_num_threads(NUM_THREADS);
	double begin = clock();
	double sum;
	sum = multipleStream(x, n);
	end = clock();
	ShowLine("MultipleThread time: ", end - begin);
	pt << sum;
}
