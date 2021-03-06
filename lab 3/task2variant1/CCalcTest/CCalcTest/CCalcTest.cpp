// CCalcTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../calc/calc/CCalc.h"
#include "../../calc/calc/СVariable.h"
#include "../../calc/calc/CFunction.h"

using namespace std;

TEST_CASE("GetName test")
{
	СVariable testVariableOne("argumentOne");
	СVariable testVariableTwo("argumnentTwo");
	CHECK(testVariableOne.GetName() == "argumentOne");
	CHECK(testVariableTwo.GetName() == "argumnentTwo");
	CFunction testFunctionOne("XPlusY");
	CHECK(testFunctionOne.GetName() == "XPlusY");
	CFunction testFunctionTwo("XMinusY");
	CHECK(testFunctionTwo.GetName() == "XMinusY");
}

TEST_CASE("EditValue test")
{
	СVariable testVariableOne("argumentOne");
	CHECK(testVariableOne.EditValue(24.0) == 24.0);
	CHECK(testVariableOne.EditValue(47.5) == 47.5);
	CHECK(testVariableOne.EditValue(0.30) == 0.30);
	CHECK(testVariableOne.EditValue(2) == 2);
}


TEST_CASE("GetValue test")
{
	СVariable testVariableOne("argumentOne");
	testVariableOne.EditValue(86);
	CHECK(testVariableOne.GetValue() == 86.0);
	testVariableOne.EditValue(24.0);
	CHECK(testVariableOne.GetValue() == 24.0);
	testVariableOne.EditValue(57.321);
	CHECK(testVariableOne.GetValue() == 57.321);
	testVariableOne.EditValue(98.98);
	CHECK(testVariableOne.GetValue() == 98.98);
}

TEST_CASE("PerformOperation test")
{
	CFunction testFunction("XPlusY");
	CHECK(testFunction.PerformOperation(12, 23, '+') == 35.0);
	CHECK(testFunction.PerformOperation(44, 23, '-') == 21.0);
	CHECK(testFunction.PerformOperation(12, 23, '*') == 276.0);
	CHECK(testFunction.PerformOperation(44, 22, '/') == 2.0);
	CHECK(testFunction.PerformOperation(44, 0, '/') == 0);
}

TEST_CASE("GetResult test")
{
	CFunction testFunction("XPlusY");
	testFunction.PerformOperation(12, 23, '+');
	CHECK(testFunction.GetResult() == 35.0);
	testFunction.PerformOperation(44, 23, '-');
	CHECK(testFunction.GetResult() == 21.0);
	testFunction.PerformOperation(12, 23, '*');
	CHECK(testFunction.GetResult() == 276.0);
	testFunction.PerformOperation(44, 22, '/');
	CHECK(testFunction.GetResult() == 2.0);
}