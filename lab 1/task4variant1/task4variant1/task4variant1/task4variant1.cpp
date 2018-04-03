// task4variant1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>

using namespace std;

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression);
void Unpack(ifstream& fileBeforeDecompression, ofstream& fileAfterDecompression);
bool CheckCommandForCorrectness(const char* command, string& nameOfCom);
bool CheckInputFile(ifstream& inFile);
bool CheckOutputFile(const char* outFile);

int main(int argc, char* argv[])
{
	if (argc <= 3)
	{
		cout << "You need 3 arguments for correct work. \n";
		return 1;
	}

	ifstream inputFile(argv[2], ios_base::binary);

	if (!inputFile.is_open())
	{
		cout << "First file is not find. Please, check your entered data. \n";
		return 1;
	}

	bool err;
	string nameOfCommand = "no";
	
	err = CheckCommandForCorrectness(argv[1], nameOfCommand);
	if (!err)
		err = CheckOutputFile(argv[3]);
	if (err)
		return 1;


	ofstream outputFile(argv[3], ios_base::binary);

	if (nameOfCommand == "pack")
		Pack(inputFile, outputFile);
	else
	{
		err = CheckInputFile(inputFile);
		if (!err)
			Unpack(inputFile, outputFile);
		else
			return 1;
	}
	 
	inputFile.close();
	outputFile.close();
	return 0;
}

bool CheckInputFile(ifstream&  inFile)
{
	inFile.seekg(0, ios::end);
	streamoff countOfKilobytes = inFile.tellg();
	if (countOfKilobytes % 2 != 0)
	{
		inFile.seekg(0, ios::beg);
		cout << "Input file has odd number bytes or empty. Please, check your input file. \n";
		return true;
	}
	else
	{
		inFile.seekg(0, ios::beg);
		return false;
	}
}

bool CheckOutputFile(const char* outFile)
{
	string typeOfFile = ".txt";
	string strOfElements = "";

	for (size_t i = 0; outFile[i] != NULL; i++)
		strOfElements += outFile[i];

	size_t countOfStr = strOfElements.length();

	if (strOfElements.find(typeOfFile, countOfStr - 5) == countOfStr - 4 && countOfStr >= 5)
		return false;
	else
	{
		cout << "Incorrect name of output file. Please, enter name of file in this format <name>.txt .\n";
		return true;
	}
}

bool CheckCommandForCorrectness(const char* strOfData, string& nameOfCom)
{
	string commandPack = "pack";
	string commandUnpack = "unpack";
	string command = "";

	for (size_t i = 0; strOfData[i] != NULL; i++)
		command += strOfData[i];

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
	char letter, element;
	while (fileBeforeDecompression.get(element))
	{
		countOfLetter = static_cast <uint8_t> (element);
		if (countOfLetter == 0)
		{
			cout << "Error. File contains zero quantity elements. \n";
			break;
		}
		fileBeforeDecompression.get(letter);
		if ((int)letter == 255)
		{
			cout << "Error. File contains unacceptable element with code 255. \n";
			break;
		}
		for (uint8_t i = 0; i < countOfLetter; i++)
		{
			if ((int)letter == 10)
				fileAfterDecompression << "\n";
			else
				fileAfterDecompression << letter;
		}
		countOfLetter = 0;
		letter = '!';
	}
}

void Pack(ifstream& fileBeforeCompression, ofstream& fileAfterCompression)
{
	uint8_t countOfLetters = 1;
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