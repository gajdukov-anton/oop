// var6task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

uint8_t FlipByte(uint8_t primordialNumber);
bool CheckTheEnteredDataForCorrectness(const char* str);


int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("Program shows difference in the order of the binary bits in the given number, please enter number at command line. \n");
		return 0;
	}
	bool err = CheckTheEnteredDataForCorrectness(argv[1]);

	if (err)
		return 1;
	int enteredNumber = stoi(argv[1]);
	uint8_t number = static_cast<uint8_t>(enteredNumber);
	number = FlipByte(number);
	int result = static_cast<int>(number);
	cout << result;
	
    return 0;
}

bool CheckTheEnteredDataForCorrectness(const char* str)
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
	catch (const std::exception& error)
	{
		cout << error.what() << "\n";
		return true;
	}
	if (checkingNumber >= 0 && checkingNumber <= 255)
		return false;
	else
	{
		cout << "Argumnet is not included in the valid range from 0 to 255.\n";
		return true;
	}
}

uint8_t FlipByte(uint8_t primordialNumber)
{
	uint8_t resultOfFlipByte = 0;
	const uint8_t MASK_OF_8_BITS = 1 << (8 - 1);

	for (int i = 0; i < 8; ++i)
	{
		resultOfFlipByte >>= 1;
		resultOfFlipByte |= primordialNumber & MASK_OF_8_BITS;
		primordialNumber <<= 1;
	}

	return resultOfFlipByte;
}