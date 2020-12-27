#include "pt4.h"
#include "omp.h"
#include "cmath"
#include <ctime>
#define NUM_THREADS 4

double oneStream(double x, int n)
{
	double sumTmp = 0, sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; ++j)
			sumTmp += (j + pow(( x + j), 1.0/4)) / (2 * i*j - 1);
		sum += 1 / sumTmp;
		sumTmp = 0;
	}
	return sum;
}

void findK(int n, int k[]) 
{
	k[3] = 0;
	for (int i = 1; i <= n; ++i) // считает по принцепу пирамиды 
		  k[0] +=i;
	k[0] = k[0] / 4;
	int c = 0;
	int key = 0;
	for (int i = 1; i <= n && k[3]==0; ++i) {
		for (int j = i; j <= n; ++j) 
		{
			c++;
			if (c > k[0]) {
				key++;
				k[key] = i;
				c = 0;
			}
		}
	}
}



double multipleStream(double x, int n)
{
	int k[4]; 
	findK(n,k);
	omp_set_num_threads(NUM_THREADS);
	double begin = clock();
	double  sum = 0;
#pragma omp parallel  sections reduction  (+:sum)
	{
#pragma omp section
		{
			int count = 0;
			double start = clock();
			for (int i = 1; i < k[1]; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= n; ++j) {
					sumTmp += (j + pow((x + j), 1.0 / 4)) / (2 * i*j - 1);
					++count;
				}
				sum += 1.0 / sumTmp;	
			}
			auto end = clock();
			Show("Thread 1 ");
			Show("Count ", count);
			ShowLine("Thread time: ", end - start);
		}

#pragma omp section
		{
			int count = 0;
			double start = clock();
			for (int i = k[1]; i < k[2]; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= n; ++j) {
					sumTmp += (j + pow((x + j), 1.0 / 4)) / (2 * i*j - 1);
					++count;
				}
				sum += 1.0 / sumTmp;
			}
			auto end = clock();

			Show("Thread 2 ");
			Show("Count ", count);
			ShowLine("Thread time: ", end - start);
		}

#pragma omp section
		{
			int count = 0;
			double start = clock();
			for (int i = k[2]; i < k[3]; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= n; ++j) {
					sumTmp += (j + pow((x + j), 1.0 / 4)) / (2 * i*j - 1);
					++count;
				}
				sum += 1.0 / sumTmp;
			}
			auto end = clock();

			Show("Thread 3 ");
			Show("Count ", count);
			ShowLine("Thread time: ", end - start);
		}

#pragma omp section
		{
			int count = 0;
			double start = clock();
			for (int i = k[3]; i <= n; ++i)
			{
				double sumTmp = 0;
				for (int j = i; j <= n; ++j) {
					sumTmp += (j + pow((x + j), 1.0 / 4)) / (2 * i*j - 1);
					++count;
				}
				sum += 1.0 / sumTmp;
			}
			auto end = clock();

			Show("Thread 4 ");
			Show("Count ", count);
			ShowLine("Thread time: ", end - start);
		}
	}
	return sum;
}



void Solve()
{
	Task("OMPBegin15");
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