// geometry.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "CGeometry.h"

using namespace std;

int main()
{
	ifstream inputFile("test2.txt");
	CGeometry geometry(cin, cout);
	cout << "Enter shape with coordinate and color or name of command as an example:" << endl;
	cout << "Circle 0.0 0.0 12.0 00ff00 ff00f0" << endl;
	while (!cin.eof() && !cin.fail())
	{
		geometry.HandleCommand();
	}
	geometry.GetMaxShape();
	geometry.GetMinShape();
    return 0;
}

