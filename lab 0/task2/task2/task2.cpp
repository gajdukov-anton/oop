// task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using n

int SumDigits(int inumber);

int main(int argc, char* argv[])
{
	for (int i = 1; i <= 1000; i++) {
		int sum = 0;
		sum = SumDigits(i);
		
		if (i % sum == 0)
		{
			cout << i;
			printf("%d", i);
			if (i < 1000)
				printf(", ");
		}
	}
    return 0;
}

int SumDigits(int number)
{
	int sum = 0;

	while (number != 0)
	{
		sum += number % 10;
		number /= 10;
	}

	return sum;
}