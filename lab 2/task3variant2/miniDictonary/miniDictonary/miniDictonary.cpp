// miniDictonary.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

const string END_OF_WORK = "...";

void FillDictonary(map <string, string>& dictonaryForFill, ifstream& fileWithDictonary);
string FindValueInDictonary(map <string, string>& dictonaryForFind, map <string, string>& newDictonaryForFind, string key);
void AddToDictonary(map <string, string>& dictonaryForWrite, pair <string, string>& newWord);
void SaveNewDictonary(map <string, string>& dictonaryForSave, ofstream& fileWithDictonary);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "rus");

	if (argc <= 1)
	{
		cout << "Please, enter name of program and name of dictonary as an example: miniDictonary.exe fileOfDictonary.txt. \n";
		return 1;
	}
		
	ifstream inputFile(argv[1]);
	map <string, string> dictonary;
	map <string, string> newDictonary;
	pair <string, string> newWord;

	if (inputFile.is_open())
		FillDictonary(dictonary, inputFile);

	inputFile.close();
	string word;
	string translation;
	getline(cin, word);
	while (word != END_OF_WORK)
	{
		translation = FindValueInDictonary(dictonary, newDictonary, word);
		if (translation == "")
		{
			cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
			getline(cin, translation);
			if (translation != "")
			{
				newWord = make_pair(word, translation);
				AddToDictonary(newDictonary, newWord);
				cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\". " << endl;
			}
			else
				cout << "Слово " << word << " проигнорировано." << endl;
		}
		else
			cout << translation << endl;
		getline(cin, word);
	}

	cout << "В словарь быи внесены изменения нажмите \"Y\" для сохранения." << endl;
	getline(cin, word);
	if (word == "Y")
	{
		ofstream outputFile(argv[1], ios_base::app);
		SaveNewDictonary(newDictonary, outputFile);
		cout << "Изменения сохранены. До свидания. " << endl;
	}
	else
		cout << "Изменения отклонены. До свидания. " << endl;

    return 0;
}

void FillDictonary(map <string, string>& dictonaryForFill, ifstream& dictonaryFile)
{
	string key = "";
	string value = "";

	while (getline(dictonaryFile, key))
	{
		getline(dictonaryFile, value);
		dictonaryForFill.insert(pair<string, string>(key, value));
	}
}

string FindValueInDictonary(map <string, string>& dictonaryForFind, map <string, string>& newDictonaryForFind, string key)
{
	auto posOfValueInOldDictonary = dictonaryForFind.find(key);
	auto posOfValueInNewDictonary = newDictonaryForFind.find(key);
	if (posOfValueInOldDictonary != dictonaryForFind.end())
		return dictonaryForFind[key];  
	if (posOfValueInNewDictonary != newDictonaryForFind.end())
		return newDictonaryForFind[key];
	return "";
}

void AddToDictonary(map <string, string>& dictonaryForWrite, pair <string, string>& newWord)
{
	dictonaryForWrite.insert(newWord);
}

void SaveNewDictonary(map <string, string>& dictonaryForSave, ofstream& dictonaryFile)
{
	for (auto it = dictonaryForSave.begin(); it != dictonaryForSave.end(); ++it)
		dictonaryFile << (*it).first << endl << (*it).second << endl;
}
