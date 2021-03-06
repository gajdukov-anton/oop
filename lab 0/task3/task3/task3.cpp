// task3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

bool ConvertStringToNumber(const char * str, int & inputNumber);

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Program displays Fibonacci numbers, please enter <FibonacciNumber.exe> <number> in the range from 1 to 2 147 483 647." << endl;
		return 0;
	}

	int limitNumber;
	bool err = ConvertStringToNumber(argv[1], limitNumber);
	if (err)
		return 1;
	if (limitNumber < 1)
	{
		cout << "Your number is smaller or equal to zero, please enter number in the range from 1 to 2 147 483 647.\n";
		return 1;
	}

	int lastNumber = 1;
	int currentNumber = 1;
	int buf;
	int counter = 1;

	cout << lastNumber << ", ";
	while (currentNumber <= limitNumber)
	{
		buf = currentNumber;
		cout << currentNumber << ", ";
		counter++;
		if (counter == 5)
		{
			cout << endl;
			counter = 0;
		}
		if (lastNumber >= INT_MAX - currentNumber)
			break;
		else
			currentNumber += lastNumber;
		lastNumber = buf;
	}
    return 0;
}

bool ConvertStringToNumber(const char * str, int& inputNumber)
{
	try
	{
		inputNumber = stoi(str);
	}
	catch (const std::invalid_argument)
	{
		cout << "Your symbol \"" << str << "\" is not a number.\n";
		return true;
	}
	catch (const std::out_of_range)
	{
		cout << "Your number is to much, please enter number in the range from 1 to 2 147 483 647.\n";
		return true;
	}
	return false;
}