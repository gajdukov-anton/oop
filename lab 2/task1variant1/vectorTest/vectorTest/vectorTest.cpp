// vectorTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>

using namespace std;

vector<float> TreatData(vector<float> vectorForFill);

vector<float> numbers1 = {1, 2, 3, 0};
vector<float> numbers1Result = {1, 2, 3};

TEST_CASE("TreatData test")
{
	numbers1 = TreatData(numbers1);
	CHECK(TreatData(numbers1) == numbers1Result);
}

vector<float> TreatData(vector<float> vectorForFill)
{
	sort(vectorForFill.begin(), vectorForFill.end());
	float minimumNumberFromVector = vectorForFill[0];
	for (size_t i = 0; i < vectorForFill.size(); i++)
	{
		vectorForFill[i] *= minimumNumberFromVector;
	}
	return vectorForFill;
}
