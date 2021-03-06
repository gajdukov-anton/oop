// testPrimeNumber.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <set>
#include <vector>

using namespace std;

unsigned int GetNewNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border);
void DeleteNotPrimeNumber(vector<bool>& vectorForFind, unsigned int lastNumber, unsigned int border);
set<unsigned int> GeneratePrimeNumber(unsigned int upperBound);

unsigned int upperBoundOne = 15;
unsigned int upperBoundTwo = 100;
unsigned int upperBoundThree = 125;
unsigned int upperBoundFour = 29;
unsigned int upperBoundFive = 200;

set<unsigned int> setOfPrimeNumber;
set<unsigned int> setResultOne = { 2, 3, 5, 7, 11, 13 };
set<unsigned int> setResultTwo = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
set<unsigned int> setResultThree = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };
set<unsigned int> setResultFour = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
set<unsigned int> setResultFive = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };



TEST_CASE("GeneratePrimeNumber test")
{
	setOfPrimeNumber = GeneratePrimeNumber(upperBoundOne);
	CHECK(setOfPrimeNumber == setResultOne);
	setOfPrimeNumber = GeneratePrimeNumber(upperBoundTwo);
	CHECK(setOfPrimeNumber == setResultTwo);
	setOfPrimeNumber = GeneratePrimeNumber(upperBoundThree);
	CHECK(setOfPrimeNumber == setResultThree);
	setOfPrimeNumber = GeneratePrimeNumber(upperBoundFour);
	CHECK(setOfPrimeNumber == setResultFour);
	setOfPrimeNumber = GeneratePrimeNumber(upperBoundFive);
	CHECK(setOfPrimeNumber == setResultFive);
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
	vector<bool> vectorOfNumbers(upperBound + 1, 0);
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