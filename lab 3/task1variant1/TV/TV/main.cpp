// TV.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CTVSet.h"
#include "string"
#include <iostream>
#include "CRemoteControl.h"

using namespace std;

int main()
{
	string command;
	CTVSet smartTV;
	CRemoteControl remoteControl(smartTV);

	while (getline(cin, command))
	{
		remoteControl.HandleCommand(command);
	}
    return 0;
}