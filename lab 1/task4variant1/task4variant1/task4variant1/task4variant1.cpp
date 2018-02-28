// task4variant1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression);
void Unpack(ifstream& fileBeforeDecompression, ofstream& fileAfterDecompression);
bool CheckCommandForCorrectness(const char* command, string& nameOfCom);

int main(int argc, char* argv[])
{
	if (argc <= 3)
	{
		cout << "You need 3 arguments for correct work. \n";
		return 1;
	}


	ifstream inputFile(argv[2], ios_base::binary);
	ofstream outputFile(argv[3], ios_base::binary);

	if (!inputFile.is_open())
	{
		cout << "First file is not find. Please, check your entered data. \n";
		return 1;
	}
	if (!outputFile.is_open())
	{
		cout << "Second file is not find. Please, check your entered data. \n";
		return 1;
	}

	bool err;
	string nameOfCommand = "no";

	err = CheckCommandForCorrectness(argv[1], nameOfCommand);
	if (err)
		return 1;

	if (nameOfCommand == "pack")
		Pack(inputFile, outputFile);
	else
		Unpack(inputFile, outputFile);

    return 0;
}

bool CheckCommandForCorrectness(const char* strOfData, string& nameOfCom)
{
	string commandPack = "pack";
	string commandUnpack = "unpack";
	string command = "";
	for (size_t i = 0; strOfData[i] != NULL; i++)
	{
		command += strOfData[i];
		//cout << command << endl;
	}
	//cout << command << endl;
	if (commandPack == command)
	{
		nameOfCom = "pack";
		return false;
	}
	else if (commandUnpack == command)
	{
		nameOfCom = "unpack";
		return false;
	}
	else
	{
		cout << "Incorrect command. Please, check your entered data. \n";
		return true;
	}
}

void Unpack(ifstream& fileBeforeDecompression, ofstream& fileAfterDecompression)
{
	uint8_t countOfLetter;
	char letter;
	while (!fileBeforeDecompression.eof())
	{
		fileBeforeDecompression >> countOfLetter;
		//cout << countOfLetter << endl;
		fileBeforeDecompression.get(letter);
		for (uint8_t i = 0; i < countOfLetter; i++)
		{
			fileAfterDecompression << letter;
		}
		countOfLetter = 0;
	}

}

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression)
{
	uint8_t countOfLetters = 1;
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

