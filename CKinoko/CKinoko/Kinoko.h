#ifndef KINOKO_H
#define KINOKO_H

typedef struct KinokoResult
{
	double *times;
	int count;
	double average;
} KinokoResult;

void CalculateAverage(KinokoResult result);
KinokoResult CreateKinokoResult(int count);

KinokoResult Kinoko(void (*task)(), int testRepeateCount, void (*beforeTaskRun)(int), void (*afterTaskRun)(int, double));

#endif