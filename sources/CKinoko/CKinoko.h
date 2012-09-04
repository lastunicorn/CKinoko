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

#ifndef KINOKO_H
#define KINOKO_H

#ifdef CKINOKO_EXPORTS
	#define CKINOKO_API __declspec(dllexport)
#else
	#define CKINOKO_API __declspec(dllimport)
#endif


/*
--------------------------------------------------------------------------------
Contains all the data requested to perform a Kinoko test.
--------------------------------------------------------------------------------
*/
typedef struct KinokoRequest
{
	void (*task)();
	int taskRunCount;
	void (*beforeTaskRun)(int);
	void (*afterTaskRun)(int, double);
} KinokoRequest;

/*
--------------------------------------------------------------------------------
Contains the results of a Kinoko test.
--------------------------------------------------------------------------------
*/
typedef struct KinokoResult
{
	double *times;
	int count;
	double average;
} KinokoResult;

/*
--------------------------------------------------------------------------------
The task from the request is run multiple times and then an average is
calculated.
--------------------------------------------------------------------------------
*/
CKINOKO_API int Kinoko(KinokoRequest request, KinokoResult **result);

/*
--------------------------------------------------------------------------------
Creates a new KinokoResult structure and initializes its array.
--------------------------------------------------------------------------------
*/
CKINOKO_API KinokoResult* CreateKinokoResult(int count);

/*
--------------------------------------------------------------------------------
Releases the memory of a KinokoResult structure.
--------------------------------------------------------------------------------
*/
CKINOKO_API DestroyKinokoResult(KinokoResult *result);

/*
--------------------------------------------------------------------------------
Calculates the average value for a KinokoResult structure. The value is stored
inside the structure.
--------------------------------------------------------------------------------
*/
void CalculateAverage(KinokoResult *result);

/*
--------------------------------------------------------------------------------
Returns the error message for the specified error code of the Kinoko function.
--------------------------------------------------------------------------------
*/
CKINOKO_API char* GetKinokoErrorMessage(int errorCode);

#endif