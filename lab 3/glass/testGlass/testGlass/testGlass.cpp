// testGlass.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../GlassProgramm/GlassProgramm/CGlass.h"

using namespace std;

TEST_CASE("glass.GetCapacity test")
{
	CGlass glass(12);
	CHECK(glass.GetCapacity() == 12);
}
