#include <time.h>
#include "Kinoko.h"

typedef struct KinokoResultS
{
	double *times;
	int count;
	double average;
} KinokoResult;

void CalculateAverage(KinokoResult result);
KinokoResult CreateKinokoResult(int count);

KinokoResult Kinoko(void (*task)(), int testRepeateCount, void (*beforeTaskRun)(int), void (*afterTaskRun)(int, double))
{
	KinokoResult result = CreateKinokoResult(testRepeateCount);
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
		result.times[i] = (t2-t1) / (double)CLOCKS_PER_SEC * 1000;

		// Announce that the Task was run.
		if (afterTaskRun != NULL)
			afterTaskRun(i, result.times[i]);
	}

	// Calculate the avarage.
	CalculateAverage(result);

	//free(times);
	return result;
}

KinokoResult CreateKinokoResult(int count)
{
	KinokoResult result;
	result.times = (double*)malloc(sizeof(double) * count);
	result.count = count;
	return result;
}

DestroyKinokoResult(KinokoResult result)
{
	free(result.times);
}

void CalculateAverage(KinokoResult result)
{
	double sum = 0;
	int i;

	for (i = 0; i < result.count; i++)
	{
		sum += result.times[i];
	}

	result.average = sum / (double)result.count;
	return result;
}