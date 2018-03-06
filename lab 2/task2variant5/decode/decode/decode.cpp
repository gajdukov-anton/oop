// decode.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

void FillVectorOfCommands(vector<string>& vectorOfCommandForFill, vector<string>& vectorofNameForFill);
int FindElementInVector(vector<string>& vectorForSearch, string elementForSearch);

int main()
{
	vector<string> vectorOfCommands(5);
	vector<string> vectorOfNameOfCommand(5);
	FillVectorOfCommands(vectorOfCommands, vectorOfNameOfCommand);
	
	size_t positionOfCommand = 0;
	size_t counter = 0;
	size_t i = 0;
	string strOfElements;
	string command;

	while (cin >> strOfElements)
	{
		positionOfCommand = strOfElements.find("&");
		if (positionOfCommand != string::npos)
		{
			i = 0;
			while (i < strOfElements.length())
			{
				while (i < positionOfCommand && i < strOfElements.length()) //можно в функцию
				{
					cout << strOfElements[i];
					i++;
				}
				//cout << i << ' ';

				i = positionOfCommand;
				//counter = positionOfCommand;
				while (i < strOfElements.length() && strOfElements[i] != ';')
				{
					command += strOfElements[i];
					i++;
					//cout << "@";
				}
				if (i < strOfElements.length())
				{
					if (strOfElements[i] == ';')
					{
						command += ";";
						i++;
					}
				}
				//cout << command << ' ';
				positionOfCommand = FindElementInVector(vectorOfCommands, command);
				//cout << positionOfCommand;
				if (positionOfCommand != -1)
					cout << vectorOfNameOfCommand[positionOfCommand];
				else
					cout << command;
				command = "";
				positionOfCommand = strOfElements.find("&", i);
			}
			cout << ' ';
		}
		else
			cout << strOfElements << ' ';
	}

    return 0;
}

void FillVectorOfCommands(vector<string>& vectorOfCommandForFill, vector<string>& vectorofNameForFill)
{
	vectorOfCommandForFill[0] = "&quot;";
	vectorOfCommandForFill[1] = "&apos;";
	vectorOfCommandForFill[2] = "&lt;";
	vectorOfCommandForFill[3] = "&gt;";
	vectorOfCommandForFill[4] = "amp;";
	vectorofNameForFill[0] = "\"";
	vectorofNameForFill[1] = "'";
	vectorofNameForFill[2] = "<";
	vectorofNameForFill[3] = ">";
	vectorofNameForFill[4] = "&";
}

int FindElementInVector(vector<string>& vectorForSearch, string elementForSearch)
{
	size_t counter = 0;
	bool isFind = false;
	while (counter < vectorForSearch.size() && !isFind)
	{
		if (elementForSearch == vectorForSearch[counter])
		{
			isFind = true;
		}
		counter++;
	}
	if (isFind)
		return counter - 1;
	else
		return -1;
}
