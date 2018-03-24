// GlassProgramm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CGlass.h"
#include <assert.h>
#include <iostream>

using namespace std;

void TestGlassCreation()
{
	CGlass validGlass(10);

	assert(validGlass.GetCapacity() == 10);
	assert(validGlass.GetWaterAmount() == 0);

	cout << "ok\n";
}


int main()
{
	TestGlassCreation();
    return 0;
}

