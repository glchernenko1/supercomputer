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
		for (int j = i; j <= 2 * n; j++)
			sumTmp += (j + log(1+ x + j)) / (2 * i*j - 1);
		sum += 1 / sumTmp;
		sumTmp = 0;
	}
	return sum;
}

double multipleStream(double x, int n)
{
	omp_set_num_threads(NUM_THREADS);
	double begin = clock();
	double  sum = 0;
#pragma omp parallel  sections reduction  (+:sum)
	{
	#pragma omp section
		{
			double start = clock();
			for (int i = 1; i <= k; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= 2*n; ++j)
					sumTmp += (j + log(1+ x + j)) / (2 * i*j - 1);
				sum += 1.0 / sumTmp;
			}
			auto end = clock();
			ShowLine("Thread time: ", end - start);
		}

		#pragma omp section
		{
			double start = clock();
			for (int i = k+1; i <= n; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= 2*n; ++j)
					sumTmp += (j + log(1+ x + j)) / (2 * i*j - 1);
				sum += 1.0 / sumTmp;
			}
			auto end = clock();
			ShowLine("Thread time: ", end - start);
		}
	}
	return sum;
}

void Solve()
{
	Task("OMPBegin12");
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