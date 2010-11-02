double CalculateAvarage(double values[], int count)
{
	double sum = 0;
	int i;
	double result;

	for (i = 0; i < count; i++)
	{
		sum += values[i];
	}

	result = sum / (double)count;
	return result;
}