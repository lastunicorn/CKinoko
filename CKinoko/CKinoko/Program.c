#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void Task();
void Pause();
void Kinoko_BeforeTaskRun(int stepIndex);
void Kinoko_AfterTaskRun(int stepIndex, double time);
double Kinoko(void (*task)(), int testRepeateCount, void (*beforeTaskRun)(int), void (*afterTaskRun)(int, double));

int count = 100000000;
int taskRunCount = 10;

void main ()
{
	double milis = Kinoko(&Task, taskRunCount, &Kinoko_BeforeTaskRun, &Kinoko_AfterTaskRun);
	
	printf("\n");
	printf("Avarage time: %.2f milisec\n", milis);
	Pause();
}

void Task()
{
	int* a = (int*)malloc(sizeof(int) * count);
	int register i;

	for (i = 0; i < count; i++)
	{
		a[i] = i;
	}

	free(a);
}

void Kinoko_BeforeTaskRun(int stepIndex)
{
	printf("Running: %d", stepIndex);
}

void Kinoko_AfterTaskRun(int stepIndex, double time)
{
	printf(" - %.2f\n", time);
}

void Pause()
{
	printf("\nPress enter to continue...");
	getchar();
	printf("\n");
}