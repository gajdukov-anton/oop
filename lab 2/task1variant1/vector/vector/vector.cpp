// vector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

bool FillTheArray(vector<float>& vectorForFill);
void PrintTheArray(vector<float>& vectorForPrint);

int main()
{
	vector<float> vectorOfNumbers;	
	bool isErr = false;

	isErr = FillTheArray(vectorOfNumbers);
	if (isErr)
		return 1;
	sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
	PrintTheArray(vectorOfNumbers);

    return 0;
}

bool FillTheArray(vector<float>& vectorForFill)
{
	char element;
	string strOfElements = "";
	float number;

	while (cin >> strOfElements)
	{
		try
		{
			number = stof(strOfElements);
			vectorForFill.push_back(number);
		}
		catch (const std::invalid_argument& error)
		{
			cout << error.what() << "\n";
			return true;
		}
	}
	return false;
}

void PrintTheArray(vector<float>& vectorForPrint)
{
	float number;

	for (size_t i = 0; i < vectorForPrint.size(); i++)
	{
		number = vectorForPrint[i] * vectorForPrint[0];
		printf("%.3f", number);
		cout << ' ';
	}
}