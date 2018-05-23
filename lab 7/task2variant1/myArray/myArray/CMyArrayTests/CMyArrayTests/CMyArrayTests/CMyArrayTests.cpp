// CMyArrayTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../CMyArray.h"
#include "../../../CMyIterator.h"
#include <iostream>
#include <string>

using namespace std;

void FillArr(CMyArray<int>& arrInt, CMyArray<string>& arrString, CMyArray<double>& arrDouble);

TEST_CASE("Constructor tests")
{
	cout << "Constructor tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyArray<int> testArr1(arrInt);

	CHECK(testArr1.GetSize() == arrInt.GetSize());
	CHECK(testArr1[0] == arrInt[0]);
}

TEST_CASE("Operator [] tests")
{
	cout << "Operator [] tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);

	CHECK(arrInt[0] == 0);
	CHECK(arrInt[3] == 3);
	CHECK(arrString[0] == "0qwerty");
	CHECK(arrString[5] == "5qwerty");
	CHECK(arrDouble[2] == 2.5);
	CHECK(arrDouble[9] == 9.5);

	arrInt[1] = 12;
	arrString[3] = "pizza";
	arrDouble[0] = 8353.2252;

	CHECK(arrInt[1] == 12);
	CHECK(arrString[3] == "pizza");
	CHECK(arrDouble[0] == 8353.2252);
}

TEST_CASE("Append tests")
{
	cout << "Append tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	arrInt.Append(123);
	arrInt.Append(0);
	arrDouble.Append(123.243);
	arrDouble.Append(123.0);
	arrString.Append("pizza");
	arrString.Append("space");

	CHECK(arrInt.GetSize() == 2);
	CHECK(arrDouble.GetSize() == 2);
	CHECK(arrString.GetSize() == 2);
	CHECK(arrInt[0] == 123);
	CHECK(arrInt[1] == 0);
	CHECK(arrDouble[0] == 123.243);
	CHECK(arrDouble[1] == 123.0);
	CHECK(arrString[0] == "pizza");
	CHECK(arrString[1] == "space");

	//arrDouble.GetAll();
}

TEST_CASE("Resize tests")
{
	cout << "Resize tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	arrString.Resize(12);
	CHECK(arrString.GetSize() == 12);
	CHECK(arrString[10] == "");
	CHECK(arrString[11] == "");
	FillArr(arrInt, arrString, arrDouble);
	arrInt.Resize(24);
	CHECK(arrInt.GetSize() == 24);
	CHECK(arrInt[20] == 0);
	CHECK(arrInt[23] == 0);
	CHECK(arrInt[10] == 0);

	arrDouble.Resize(20);
	CHECK(arrDouble[19] == 0);
	CHECK(arrDouble[14] == 0);
	CHECK(arrDouble.GetSize() == 20);
}

TEST_CASE("Operator = tests")
{
	cout << "Operator = tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyArray<int> testArr1;
	CMyArray<string> testArr2 = arrString;
	arrInt = testArr1;
	CHECK(arrInt.GetSize() == testArr1.GetSize());
	CHECK(testArr2.GetSize() == arrString.GetSize());
}

TEST_CASE("Clear tests")
{
	cout << "Clear tests started" << endl;

	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	arrInt.Clear();
	CHECK(arrInt.GetSize() == 0);
}


TEST_CASE("CMyIterator constructor tests")
{
	cout << "CMyIterator constructor tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);

	CMyIterator<int> itInt;
	CMyIterator<string> itStr;
	CMyIterator<double> itDouble;

	itInt = arrInt.Begin();
	CHECK(itInt.GetValue() == arrInt[0]);
	arrInt[0] = 120;
	CHECK(itInt.GetValue() == arrInt[0]);
	itInt = arrInt.End();
	CHECK(itInt.GetValue() == arrInt[9]);
	arrInt.Resize(12);

	itStr = arrString.Begin();
	CHECK(itStr.GetValue() == arrString[0]);
	itStr = arrString.End();
	CHECK(itStr.GetValue() == arrString[9]);

	itDouble = arrDouble.Begin();
	CHECK(itDouble.GetValue() == arrDouble[0]);
	itDouble = arrDouble.End();
	CHECK(itDouble.GetValue() == arrDouble[9]);
}

TEST_CASE("CMyIterator operator++ tests")
{
	cout << "CMyIterator operator++ tests" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyIterator<int> it;
	it = arrInt.End();
	++it;
	CHECK(it.GetValue() == arrInt[9]);
	/*CHECK(it.GetOffset() == 1);
	--it;
	CHECK(it.GetValue() == arrInt[0]);
	--it;
	CHECK(it.GetOffset() == 0);
	CHECK(it.GetValue() == arrInt[0]);*/
}

void FillArr(CMyArray<int>& arrInt, CMyArray<string>& arrString, CMyArray<double>& arrDouble)
{
	for (int i = 0; i < 10; i++)
	{
		arrInt.Append(i);
	}
	for (int i = 0; i < 10; i++)
	{
		arrString.Append(to_string(i) + "qwerty");
	}
	for (int i = 0; i < 10; i++)
	{
		arrDouble.Append(i + 0.5);
	}
}