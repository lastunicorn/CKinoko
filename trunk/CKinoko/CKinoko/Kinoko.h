// CKinoko
// Copyright (C) 2010 Dust in the Wind
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
	#define DECLSPEC __declspec(dllexport)
#else
	#define DECLSPEC __declspec(dllimport)
#endif

typedef struct KinokoRequest
{
	void (*task)();
	int taskRunCount;
	void (*beforeTaskRun)(int);
	void (*afterTaskRun)(int, double);
} KinokoRequest;

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
DECLSPEC int Kinoko(KinokoRequest request, KinokoResult **result);

/*
--------------------------------------------------------------------------------
Creates a new KinokoResult structure and initializes its array.
--------------------------------------------------------------------------------
*/
KinokoResult* CreateKinokoResult(int count);

/*
--------------------------------------------------------------------------------
Releases the memory of a KinokoResult structure.
--------------------------------------------------------------------------------
*/
DestroyKinokoResult(KinokoResult *result);

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
DECLSPEC char* GetKinokoErrorMessage(int errorCode);

#endif