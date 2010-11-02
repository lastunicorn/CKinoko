#include <time.h>

double CalculateAvarage(double values[], int count);

double Kinoko(void (*task)(), int testRepeateCount, void (*beforeTaskRun)(int), void (*afterTaskRun)(int, double))
{
	double* times = (double*)malloc( sizeof(double) * testRepeateCount);
	double avarage = 0;
	clock_t t1;
	clock_t t2;

	// The Task is run multiple times and then an avarage is calculated.

	int i;
	for (i = 0; i < testRepeateCount; i++)
	{
		// Announce that the Task is about to be run.
		if (beforeTaskRun != NULL)
			beforeTaskRun(i);

		// Run the Task.
		t1 = clock();
		task();
		t2 = clock();

		// Calculate and store the time in which the task run.
		times[i] = (t2-t1) / (double)CLOCKS_PER_SEC * 1000;
	
		// Announce that the Task was run.
		if (afterTaskRun != NULL)
			afterTaskRun(i, times[i]);
	}

	// Calculate the avarage.
	avarage = CalculateAvarage(times, testRepeateCount);

	free(times);
	return avarage;
}