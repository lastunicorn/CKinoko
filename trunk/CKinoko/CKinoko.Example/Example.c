// CKinoko
// Copyright (C) 2011 Dust in the Wind
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "Kinoko.h"
#include "windows.h"


void Task();
void Pause();
void Kinoko_BeforeTaskRun(int stepIndex);
void Kinoko_AfterTaskRun(int stepIndex, double time);

/*
--------------------------------------------------------------------------------
The number of times the task is tested.
--------------------------------------------------------------------------------
*/
int taskRunCount = 10;

/*
--------------------------------------------------------------------------------
The time in miliseconds for the tested task to sleep.
--------------------------------------------------------------------------------
*/
int sleepMilli = 300;

/*
--------------------------------------------------------------------------------
The entry point of the application.
--------------------------------------------------------------------------------
*/
void main ()
{
	KinokoRequest request;
	KinokoResult *result;
	int errorCode;

	printf("CKinoko usage example\n");
	printf("===============================================================================\n");
	printf("Running a fake task that junst sleeps for %d milliseconds.\n", sleepMilli);
	printf("The test is repeated %d times and the avarage time is displayed.\n", taskRunCount);
	printf("\n");

	// Create the request for Kinoko.
	request.task = &Task;
	request.taskRunCount = taskRunCount;
	request.beforeTaskRun = &Kinoko_BeforeTaskRun;
	request.afterTaskRun = &Kinoko_AfterTaskRun;

	// Run Kinoko.
	errorCode = Kinoko(request, &result);

	// Display the result.
	printf("\n");
	if (errorCode == 0)
	{
		printf("Average time: %.2f milisec\n", result->average);
	}
	else
	{
		printf("Error");
		printf(GetKinokoErrorMessage(errorCode));
	}

	DestroyKinokoResult(result);

	Pause();
}

/*
--------------------------------------------------------------------------------
The task that I want to test.
--------------------------------------------------------------------------------
*/
void Task()
{
	// Just sleep for a while.
	Sleep(sleepMilli);
	return;
}

/*
--------------------------------------------------------------------------------
Function called every time before the task is run.
--------------------------------------------------------------------------------
*/
void Kinoko_BeforeTaskRun(int stepIndex)
{
	printf("Running: %d", stepIndex);
}

/*
--------------------------------------------------------------------------------
Function called every time after the task is run.
--------------------------------------------------------------------------------
*/
void Kinoko_AfterTaskRun(int stepIndex, double time)
{
	printf(" - %.2f\n", time);
}

/*
--------------------------------------------------------------------------------
Pauses the console until the user presses a key.
--------------------------------------------------------------------------------
*/
void Pause()
{
	printf("\nPress enter to continue...");
	getchar();
	printf("\n");
}