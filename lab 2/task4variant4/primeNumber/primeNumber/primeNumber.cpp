// primeNumber.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <set>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

using namespace std;

vector<bool> vectorOfNumbers(100000001);
set<unsigned int> setOfPrimeNumber;

unsigned int GetNewNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border);
void DeleteNotPrimeNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border);
set<unsigned int> GeneratePrimeNumber(unsigned int upperBound);
void WriteSetOfPrimeNumbers(set<unsigned int>& setOfPrimeNumForWrite);

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Please, enter name of program and upper bound as an example: primeNumber.exe \"upper bound\"" << endl;
		return 1;
	}
	unsigned int border = stoi(argv[1]);
	setOfPrimeNumber = GeneratePrimeNumber(border);
	WriteSetOfPrimeNumbers(setOfPrimeNumber);
    return 0;
}

unsigned int GetNewNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border)
{
	lastNumber++;

	while (lastNumber <= border && vectorForFind[lastNumber])
	{
		lastNumber++;
	}
	return lastNumber;
}

void DeleteNotPrimeNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border)
{
	unsigned int primeNumber = lastNumber;
	if (lastNumber <= 10000)
	{
		lastNumber *= lastNumber;
		while (lastNumber <= border)
		{
			vectorForFind[lastNumber] = true;
			lastNumber += primeNumber;
		}
	}
}

set<unsigned int> GeneratePrimeNumber(unsigned int upperBound)
{
	set<unsigned int> setForGeneratePrimeNumber;

	unsigned int number = 1;
	while (number <= upperBound)
	{
		number = GetNewNumber(vectorOfNumbers, number, upperBound);
		if (number <= upperBound)
		{
			DeleteNotPrimeNumber(vectorOfNumbers, number, upperBound);
			setForGeneratePrimeNumber.insert(number);
		}
	}
	return setForGeneratePrimeNumber;
}

void WriteSetOfPrimeNumbers(set<unsigned int>& setOfPrimeNumForWrite)
{
	cout << setOfPrimeNumForWrite.size() << endl;
	for (auto it = setOfPrimeNumForWrite.begin(); it != setOfPrimeNumForWrite.end(); it++)
		cout << *it << ' ';
}