// task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

bool FindText(ifstream& inFile, string str);

int main(int argc, char* argv[])
{
	if (argc <= 2)
	{
		cout << "You need enter textfound.exe and <file name> and <text to search> for correct work. \n";
		return 1;
	}


	ifstream inputFile(argv[1]);

	if (!inputFile.is_open())
	{
		cout << "File is not found, please check your data and repeat again.\n";
		return 1;
	}

	if (!strlen(argv[2]))
	{
		cout << "You entered empty string. Please, check your data and try again.\n";
		return 1;
	}

	bool isFindStr = FindText(inputFile, argv[2]);

	if (!isFindStr)
	{
		cout << "Text not found.\n";
		return 1;
	}

	cout.flush();
	return 0;
}

bool FindText(ifstream& inFile, string str)
{
	string strForSearch;
	int numberOfCurrentStr = 0;
	int numberOfSoughtStr = 0;

	while (!inFile.eof())
	{
		getline(inFile, strForSearch);
		++numberOfCurrentStr;

		if (strForSearch.find(str) != string::npos)
		{
			numberOfSoughtStr = numberOfCurrentStr;
			cout << numberOfSoughtStr << endl;
		}
	}

	if (numberOfSoughtStr != 0)
		return true;
	else
		return false;
}
