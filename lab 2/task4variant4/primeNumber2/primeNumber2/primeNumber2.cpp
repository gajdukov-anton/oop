// primeNumber.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <set>
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

using namespace std;

const unsigned int MAX_NUMBER_FOR_TREAT = 10000;

bool CheckInputDataForCorrectness(const char* str);
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

	bool err = CheckInputDataForCorrectness(argv[1]);
	if (err)
		return 1;

	unsigned int border = stoi(argv[1]);
	set<unsigned int> setOfPrimeNumber;
	setOfPrimeNumber = GeneratePrimeNumber(border);
	WriteSetOfPrimeNumbers(setOfPrimeNumber);

	return 0;
}

bool CheckInputDataForCorrectness(const char* str)
{
	int checkingNumber;
	try
	{
		checkingNumber = stoi(str);
		assert(true);
	}
	catch (const std::invalid_argument& error)
	{
		cout << error.what() << "\n";
		return true;
	}

	return false;
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
	if (lastNumber <= MAX_NUMBER_FOR_TREAT)
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
	vector<bool> vectorOfNumbers(upperBound + 1, false);
	unsigned int currentNumber = 1;

	while (currentNumber <= upperBound)
	{
		currentNumber = GetNewNumber(vectorOfNumbers, currentNumber, upperBound);
		if (currentNumber <= upperBound)
		{
			DeleteNotPrimeNumber(vectorOfNumbers, currentNumber, upperBound);
			setForGeneratePrimeNumber.insert(currentNumber);
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