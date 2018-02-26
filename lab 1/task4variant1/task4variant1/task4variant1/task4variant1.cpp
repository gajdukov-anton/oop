// task4variant1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression);

int main(int argc, char* argv[])
{
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	Pack(inputFile, outputFile);
	/*int countOfLetters = 1;
	int size = 1;
	char curLetter = 'a';
	char pastLetter = 'a';
	inputFile.get(pastLetter);
	while (!inputFile.eof())
	{
		inputFile.get(curLetter);
		while (curLetter == pastLetter && !inputFile.eof() && countOfLetters != 255)
		{
			++countOfLetters;
			inputFile.get(curLetter);
		}
		cout << countOfLetters << ' ' << pastLetter << ' ';
		pastLetter = curLetter;
		countOfLetters = 1;
	}*/
    return 0;
}

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression)
{
	int countOfLetters = 1;
	int size = 1;
	char curLetter = 'a';
	char pastLetter = 'a';
	fileBeforeCompression.get(pastLetter);
	while (!fileBeforeCompression.eof())
	{
		fileBeforeCompression.get(curLetter);
		while (curLetter == pastLetter && !fileBeforeCompression.eof() && countOfLetters != 255)
		{
			++countOfLetters;
			fileBeforeCompression.get(curLetter);
		}
		fileAfterCompression << countOfLetters << pastLetter;
		pastLetter = curLetter;
		countOfLetters = 1;
	}
}

