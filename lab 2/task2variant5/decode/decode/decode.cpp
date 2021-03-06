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
void TreatText(size_t& counter, string& strAfterTreat, string strBeforeTreat);
string TreatCommand(size_t& counter, string strBeforeTreat, vector<string>& vectorOfCommands, vector<string>& vectorOfNameOfCommand);
string HtmlDecode(string strForDecode);


int main()
{
	string strOfElements;
	string str = "";
	
	while (getline(cin, strOfElements))
	{
		str = HtmlDecode(strOfElements);
		cout << str << endl;
		str = "";
	}

    return 0;
}

void FillVectorOfCommands(vector<string>& vectorOfCommandForFill, vector<string>& vectorofNameForFill)
{
	vectorOfCommandForFill[0] = "&quot;";
	vectorOfCommandForFill[1] = "&apos;";
	vectorOfCommandForFill[2] = "&lt;";
	vectorOfCommandForFill[3] = "&gt;";
	vectorOfCommandForFill[4] = "&amp;";
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
			isFind = true;
		counter++;
	}
	if (isFind)
		return counter - 1;
	else
		return -1;
}

void TreatText(size_t& counter, string& strAfterTreat, string strBeforeTreat)
{
	size_t lengthOfStr = strBeforeTreat.length();
	size_t textBorder = strBeforeTreat.find("&", counter);
	while (counter < textBorder && counter < lengthOfStr) 
	{
		strAfterTreat += strBeforeTreat[counter];
		counter++;
	}
	counter = textBorder;
}

string TreatCommand(size_t& counter, string strBeforeTreat, vector<string>& vectorOfCommands, vector<string>& vectorOfNameOfCommand)
{
	string command = "";
	string strAfterTreat = "";
	size_t textBorder = strBeforeTreat.length();
	size_t lengthOfStr = strBeforeTreat.length();

	while (counter < lengthOfStr && strBeforeTreat[counter] != ';')
	{
		command += strBeforeTreat[counter];
		counter++;
	}
	if (counter < lengthOfStr)
	{
		if (strBeforeTreat[counter] == ';')
		{
			command += ";";
			counter++;
		}
	}
	textBorder = FindElementInVector(vectorOfCommands, command);
	if (textBorder != -1)
		strAfterTreat += vectorOfNameOfCommand[textBorder];
	else
		strAfterTreat += command;

	return strAfterTreat;
}

string HtmlDecode(string strForDecode)
{
	vector<string> vectorOfCommands(5);
	vector<string> vectorOfNameOfCommand(5);
	FillVectorOfCommands(vectorOfCommands, vectorOfNameOfCommand);
	string strAfterDecode = "";
	size_t positionOfCommand = 0;
	size_t i = 0;

	positionOfCommand = strForDecode.find("&");
	if (positionOfCommand != string::npos)
	{
		i = 0;
		while (i < strForDecode.length())
		{
			TreatText(i, strAfterDecode, strForDecode);
			strAfterDecode += TreatCommand(i, strForDecode, vectorOfCommands, vectorOfNameOfCommand);
			positionOfCommand = strForDecode.find("&", i);
		}
		strAfterDecode += ' ';
	}
	else
		strAfterDecode += strForDecode + ' ';
	return strAfterDecode;
}