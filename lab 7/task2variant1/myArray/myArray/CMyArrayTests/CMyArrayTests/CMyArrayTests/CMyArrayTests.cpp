// CMyArrayTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../CMyArray.h"
#include "../../../CMyRevIterator.h"
#include "../../../CMyIterator.h"
#include <iostream>
#include <string>

using namespace std;

const string OUT_OF_RANGE_EXCEPTION = "index is out of range";


void FillArr(CMyArray<int>& arrInt, CMyArray<std::string>& arrString, CMyArray<double>& arrDouble);

TEST_CASE("Constructor tests")
{
	cout << "Constructor tests started" << endl;
	CMyArray<int> intArr{1, 2, 3, 4};
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyArray<int> testArr1(arrInt);

	CHECK(testArr1.GetSize() == arrInt.GetSize());
	CHECK(testArr1[0] == arrInt[0]);
	CMyArray<int> testArr2(move(testArr1));
	CHECK(testArr2.GetSize() == arrInt.GetSize());
	CHECK(testArr2[8] == arrInt[8]);
	CHECK(testArr1.GetSize() == 0);
	CHECK(intArr[0] == 1);
	CHECK(intArr[1] == 2);
	CHECK(intArr[2] == 3);
	CHECK(intArr[3] == 4);
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

	try
	{
		arrInt[100] = 0;
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
	try
	{
		arrString[100] = "0";
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
	try
	{
		arrDouble[100] = 0;
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
	try
	{
		int number;
		number = arrInt[100];
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
	try
	{
		string str;
		str = arrString[100];
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
	try
	{
		double number;
		number = arrDouble[100];
	}
	catch (out_of_range error)
	{
		CHECK(error.what() == OUT_OF_RANGE_EXCEPTION);
	}
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
	CMyArray<int> intArr{1, 2, 3, 4};
	FillArr(arrInt, arrString, arrDouble);
	CMyArray<int> testArr1;
	CMyArray<string> testArr2 = arrString;
	arrInt = testArr1;
	CHECK(arrInt.GetSize() == testArr1.GetSize());
	CHECK(testArr2.GetSize() == arrString.GetSize());
	intArr = CMyArray<int>{1, 3, 4};
	CHECK(intArr.GetSize() == 3);
	CHECK(intArr[0] == 1);
	CHECK(intArr[1] == 3);
	CHECK(intArr[2] == 4);
}

TEST_CASE("Clear tests")
{
	cout << "Clear tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	CMyArray<int> arr{1, 2, 3};
	FillArr(arrInt, arrString, arrDouble);
	arrInt.Clear();
	arr.Clear();
	CHECK(arr.GetSize() == 0);
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
	itInt = arrInt.End();
	CHECK(itInt.GetValue() == arrInt[11]);

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
	cout << "CMyIterator operator++ tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyIterator<int> itInt;
	CMyIterator<string> itStr;
	CMyIterator<double> itDouble;
	itInt = arrInt.Begin();
	itStr = arrString.Begin();
	itDouble = arrDouble.Begin();
	++itStr;
	++itDouble;
	++itInt;
	CHECK(itInt.GetValue() == arrInt[1]);
	CHECK(itStr.GetValue() == arrString[1]);
	CHECK(itDouble.GetValue() == arrDouble[1]);
	itStr++;
	itDouble++;
	itInt++;
	CHECK(itInt.GetValue() == arrInt[2]);
	CHECK(itStr.GetValue() == arrString[2]);
	CHECK(itDouble.GetValue() == arrDouble[2]);
}

TEST_CASE("CMyIterator operator-- tests")
{
	cout << "CMyIterator operator-- tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyIterator<int> itInt;
	CMyIterator<string> itStr;
	CMyIterator<double> itDouble;
	itInt = arrInt.End();
	itStr = arrString.End();
	itDouble = arrDouble.End();
	--itStr;
	--itDouble;
	--itInt;
	CHECK(itInt.GetValue() == arrInt[8]);
	CHECK(itStr.GetValue() == arrString[8]);
	CHECK(itDouble.GetValue() == arrDouble[8]);
	itStr--;
	itDouble--;
	itInt--;
	CHECK(itInt.GetValue() == arrInt[7]);
	CHECK(itStr.GetValue() == arrString[7]);
	CHECK(itDouble.GetValue() == arrDouble[7]);
}


TEST_CASE("CMyIterator operator== tests")
{
	cout << "CMyIterator operator== tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyIterator<int> itInt;
	CMyIterator<string> itStr;
	CMyIterator<double> itDouble;
	CMyIterator<int> itInt2;
	CMyIterator<string> itStr2;
	CMyIterator<double> itDouble2;
	itInt = arrInt.End();
	itStr = arrString.End();
	itDouble = arrDouble.End();
	itInt2 = arrInt.End();
	itStr2 = arrString.End();
	itDouble2 = arrDouble.End();
	CHECK(itInt == itInt2);
	CHECK(itStr == itStr2);
	CHECK(itDouble == itDouble2);
}

TEST_CASE("CMyIterator operator!= tests")
{
	cout << "CMyIterator operator!= tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyIterator<int> itInt;
	CMyIterator<string> itStr;
	CMyIterator<double> itDouble;
	CMyIterator<int> itInt2;
	CMyIterator<string> itStr2;
	CMyIterator<double> itDouble2;
	itInt = arrInt.End();
	itStr = arrString.End();
	itDouble = arrDouble.End();
	itInt2 = arrInt.Begin();
	itStr2 = arrString.Begin();
	itDouble2 = arrDouble.Begin();
	CHECK(itInt != itInt2);
	CHECK(itStr != itStr2);
	CHECK(itDouble != itDouble2);
}

TEST_CASE("CMyRevIterator constructor tests")
{
	cout << "CMyRevIterator constructor tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);

	CMyRevIterator<int> itInt;
	CMyRevIterator<string> itStr;
	CMyRevIterator<double> itDouble;

	itInt = arrInt.RBegin();
	CHECK(itInt.GetValue() == arrInt[9]);
	arrInt[9] = 120;
	CHECK(itInt.GetValue() == arrInt[9]);
	itInt = arrInt.REnd();
	CHECK(itInt.GetValue() == arrInt[0]);
	arrInt.Resize(12);
	itInt = arrInt.RBegin();
	CHECK(itInt.GetValue() == arrInt[11]);

	itStr = arrString.RBegin();
	CHECK(itStr.GetValue() == arrString[9]);
	itStr = arrString.REnd();
	CHECK(itStr.GetValue() == arrString[0]);

	itDouble = arrDouble.RBegin();
	CHECK(itDouble.GetValue() == arrDouble[9]);
	itDouble = arrDouble.REnd();
	CHECK(itDouble.GetValue() == arrDouble[0]);
}

TEST_CASE("CMyRevIterator operator++ tests")
{
	cout << "CMyRevIterator operator++ tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyRevIterator<int> itInt;
	CMyRevIterator<string> itStr;
	CMyRevIterator<double> itDouble;
	itInt = arrInt.RBegin();
	itStr = arrString.RBegin();
	itDouble = arrDouble.RBegin();
	++itStr;
	++itDouble;
	++itInt;
	CHECK(itInt.GetValue() == arrInt[8]);
	CHECK(itStr.GetValue() == arrString[8]);
	CHECK(itDouble.GetValue() == arrDouble[8]);
	itStr++;
	itDouble++;
	itInt++;
	CHECK(itInt.GetValue() == arrInt[7]);
	CHECK(itStr.GetValue() == arrString[7]);
	CHECK(itDouble.GetValue() == arrDouble[7]);
}

TEST_CASE("CMyRevIterator operator-- tests")
{
	cout << "CMyRevIterator operator-- tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyRevIterator<int> itInt;
	CMyRevIterator<string> itStr;
	CMyRevIterator<double> itDouble;
	itInt = arrInt.REnd();
	itStr = arrString.REnd();
	itDouble = arrDouble.REnd();
	--itStr;
	--itDouble;
	--itInt;
	CHECK(itInt.GetValue() == arrInt[1]);
	CHECK(itStr.GetValue() == arrString[1]);
	CHECK(itDouble.GetValue() == arrDouble[1]);
	itStr--;
	itDouble--;
	itInt--;
	CHECK(itInt.GetValue() == arrInt[2]);
	CHECK(itStr.GetValue() == arrString[2]);
	CHECK(itDouble.GetValue() == arrDouble[2]);
}

TEST_CASE("CMyRevIterator operator== tests")
{
	cout << "CMyRevIterator operator== tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyRevIterator<int> itInt;
	CMyRevIterator<string> itStr;
	CMyRevIterator<double> itDouble;
	CMyRevIterator<int> itInt2;
	CMyRevIterator<string> itStr2;
	CMyRevIterator<double> itDouble2;
	itInt = arrInt.REnd();
	itStr = arrString.REnd();
	itDouble = arrDouble.REnd();
	itInt2 = arrInt.REnd();
	itStr2 = arrString.REnd();
	itDouble2 = arrDouble.REnd();
	CHECK(itInt == itInt2);
	CHECK(itStr == itStr2);
	CHECK(itDouble == itDouble2);
}

TEST_CASE("CMyRevIterator operator!= tests")
{
	cout << "CMyRevIterator operator!= tests started" << endl;
	CMyArray<int> arrInt;
	CMyArray<string> arrString;
	CMyArray<double> arrDouble;
	FillArr(arrInt, arrString, arrDouble);
	CMyRevIterator<int> itInt;
	CMyRevIterator<string> itStr;
	CMyRevIterator<double> itDouble;
	CMyRevIterator<int> itInt2;
	CMyRevIterator<string> itStr2;
	CMyRevIterator<double> itDouble2;
	itInt = arrInt.REnd();
	itStr = arrString.REnd();
	itDouble = arrDouble.REnd();
	itInt2 = arrInt.RBegin();
	itStr2 = arrString.RBegin();
	itDouble2 = arrDouble.RBegin();
	CHECK(itInt != itInt2);
	CHECK(itStr != itStr2);
	CHECK(itDouble != itDouble2);
}

void FillArr(CMyArray<int>& arrInt, CMyArray<std::string>& arrString, CMyArray<double>& arrDouble)
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