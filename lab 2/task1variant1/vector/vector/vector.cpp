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
void TreatData(vector<float>& vectorForFill);
void PrintTheArray(vector<float>& vectorForPrint);

int main()
{
	vector<float> vectorOfNumbers;	
	bool isErr = false;

	isErr = FillTheArray(vectorOfNumbers);
	if (isErr)
		return 1;
	TreatData(vectorOfNumbers);
	PrintTheArray(vectorOfNumbers);

    return 0;
}

bool FillTheArray(vector<float>& vectorForFill)
{
	string strOfElements = "";
	float number;

	while (cin >> strOfElements)
	{
		try
		{
			number = stof(strOfElements);
		}
		catch (const std::invalid_argument& error)
		{
			cout << error.what() << "\n";
			return true;
		}
		vectorForFill.push_back(number);
	}
	return false;
}

void PrintTheArray(vector<float>& vectorForPrint)
{
	
	for (size_t i = 0; i < vectorForPrint.size(); i++)
	{
		printf("%.3f", vectorForPrint[i]);
		cout << ' ';
	}
}

void TreatData(vector<float>& vectorForFill)
{
	sort(vectorForFill.begin(), vectorForFill.end());
	float minimumNumberFromVector = vectorForFill[0];
	for (size_t i = 0; i < vectorForFill.size(); i++)
	{
		vectorForFill[i] *= minimumNumberFromVector;
	}
}