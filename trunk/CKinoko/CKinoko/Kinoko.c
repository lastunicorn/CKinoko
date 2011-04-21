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
#include <time.h>
#include "Kinoko.h"

/*
--------------------------------------------------------------------------------
The task from the request is run multiple times and after that an average of the
running times is calculated.
--------------------------------------------------------------------------------
Error codes:
	0 - No error.
	2 - Invalid request. The 'task' is null.
	3 - Invalid request. The 'taskRunCount' is less then 1.
--------------------------------------------------------------------------------
*/
int Kinoko(KinokoRequest request, KinokoResult **result)
{
	clock_t t1;
	clock_t t2;
	double intervalMilli;
	int i;

	*result = NULL;

	// Check the request structure to contain all the necessary data.

	if (request.task == NULL)
		return 2;

	if (request.taskRunCount <= 0)
		return 3;

	// Create the result structure.

	*result = CreateKinokoResult(request.taskRunCount);
	
	// Run the task.
	for (i = 0; i < request.taskRunCount; i++)
	{
		// Announce that the task is about to be run.
		if (request.beforeTaskRun != NULL)
			request.beforeTaskRun(i);

		// Run the Task.
		t1 = clock();
		request.task();
		t2 = clock();

		// Calculate the time that was necessary to run the task.
		intervalMilli = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000;
		
		// Store the time interval.
		(*result)->times[i] = intervalMilli;

		// Announce that the task was run.
		if (request.afterTaskRun != NULL)
			request.afterTaskRun(i, intervalMilli);
	}

	// Calculate the average.
	CalculateAverage(*result);

	return 0;
}

/*
--------------------------------------------------------------------------------
Creates a new KinokoResult structure and initializes its array.
--------------------------------------------------------------------------------
*/
KinokoResult* CreateKinokoResult(int count)
{
	KinokoResult *result = (KinokoResult*)malloc(sizeof(KinokoResult));
	result->times = (double*)malloc(sizeof(double) * count);
	result->count = count;
	result->average = -1;
	return result;
}

/*
--------------------------------------------------------------------------------
Releases the memory of a KinokoResult structure.
--------------------------------------------------------------------------------
*/
DestroyKinokoResult(KinokoResult *result)
{
	if (result != NULL)
	{
		free(result->times);
		free(result);
	}
}

/*
--------------------------------------------------------------------------------
Calculates the average value for a KinokoResult structure. The value is stored
inside the structure.
--------------------------------------------------------------------------------
*/
void CalculateAverage(KinokoResult *result)
{
	double sum = 0;
	int i;

	for (i = 0; i < result->count; i++)
	{
		sum += result->times[i];
	}

	result->average = sum / (double)result->count;
}

/*
--------------------------------------------------------------------------------
Returns the error message for the specified error code of the Kinoko function.
--------------------------------------------------------------------------------
*/
char* GetKinokoErrorMessage(int errorCode)
{
	switch(errorCode)
	{
	case 0:
		return "No error.";

	case 1:
		return "'request' parameter is null.";
	
	case 2:
		return "Invalid request. The 'task' is null.";

	case 3:
		return "Invalid request. The 'taskRunCount' is less then 1.";

	default:
		return "";
	}
}