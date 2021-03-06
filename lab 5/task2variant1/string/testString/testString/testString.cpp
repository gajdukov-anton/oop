// testString.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../string/CMyString.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string TEST_STR_ONE = "qwerty";
const string EMPTY_STR = "";
const string TEST_STR_TWO = "pizza";
const string TEST_STR_THREE = "pizzaqwerty";
const string OUT_OF_RANGE_EXCEPTION = "the index should be in the range from 0 to the length of the string";
const string OUT_OF_LENGTH = "the length is out of range current string";


TEST_CASE("CMyString constructor test")
{
	cout << "CMyString constructor tests started" << endl;
	string strResult = "qwerty";
	CMyString myStr("qwerty");
	CMyString myStr1("pizza", 5);
	CMyString myStr2("pizzaqwerty", 11);
	CMyString myStr3(strResult);
	CMyString myStr4("pizza");
	CMyString myStr5(move(myStr4));
	CMyString myStr7("qwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwerty");
	CHECK(myStr7.GetStringData() == string("qwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwerty"));
	CHECK(myStr7.GetLength() == 90);
	CHECK(myStr4.GetLength() == 0);
	CHECK(myStr4.GetStringData() == "");
	CHECK(myStr5.GetLength() == 5);
	CHECK(myStr5.GetStringData() == TEST_STR_TWO);
	CHECK(myStr.GetLength() == 6);
	CHECK(myStr1.GetLength() == 5);
	CHECK(myStr.GetStringData() == TEST_STR_ONE);
	CHECK(myStr1.GetStringData() == TEST_STR_TWO);
	CHECK(myStr2.GetStringData() == TEST_STR_THREE);
	CHECK(myStr2.GetLength() == 11);
	CHECK(myStr3.GetStringData() == strResult);
	CHECK(myStr3.GetLength() == 6);
	ostringstream stream;
	CMyString myStr6("pizza\0qwerty\0pizza", 18);
	for (int i = 0; i < myStr6.GetLength(); ++i)
	{
		if (myStr6[i] == '\0')
			stream << "\\0";
		else
			stream << myStr6[i];
	}
	CHECK(stream.str() == "pizza\\0qwerty\\0pizza");
	CHECK(myStr6.GetLength() == 18);
}

TEST_CASE("Clear function test")
{
	cout << "Clear function tests started" << endl;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	str.Clear();
	str1.Clear();
	CHECK(str.GetStringData() == EMPTY_STR);
	CHECK(str.GetLength() == 0);
	CHECK(str1.GetStringData() == EMPTY_STR);
	CHECK(str1.GetLength() == 0);
}

TEST_CASE("Operator = test")
{
	cout << "Operator = tests started" << endl;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	CMyString str2;
	str = str1;
	str2 = str;
	str = str;
	CHECK(str.GetStringData() == TEST_STR_TWO);
	CHECK(str2.GetStringData() == TEST_STR_TWO);
	CHECK(str.GetLength() == 5);
	CHECK(str2.GetLength() == 5);
}

TEST_CASE("Operator += test")
{
	cout << "Operator += tests started" << endl;
	string s = "qwertyqwerty";
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	CMyString str2;
	str1 += str;
	str += str;
	str2 += str2;
	CHECK(str2.GetStringData() == EMPTY_STR);
	CHECK(str2.GetLength() == 0);
	str2 += str;
	CHECK(str2.GetStringData() == s);
	CHECK(str2.GetLength() == 12);
	CHECK(str1.GetStringData() == TEST_STR_THREE);
	CHECK(str.GetStringData() == s);
	CHECK(str1.GetLength() == 11);
}

TEST_CASE("Opearator == test")
{
	cout << "Operator == tests started" << endl;
	CMyString str("qwerty");
	CMyString str1("qwerty");
	CMyString str2;
	CMyString str3;
	CHECK(str == str1);
	CHECK(str2 == str3);
}

TEST_CASE("Opearator != test")
{
	cout << "Operator != tests started" << endl;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	CMyString str2;
	CMyString str3("qwert");
	CMyString str4("qwerts");
	CHECK(str != str1);
	CHECK(str != str2);
	CHECK(str1 != str2);
	CHECK(str != str3);
	CHECK(str != str4);
}

TEST_CASE("Operator + (CMyString with CMyString) test")
{
	cout << "Operator + (CMyString with CMyString) test started" << endl;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	CMyString str2;
	string s = "qwertyqwerty";
	str2 = str1 + str;
	CHECK(str2.GetStringData() == TEST_STR_THREE);
	str2.Clear();
	str2 = str1 + str;
	str = str + str;
	CHECK(str2.GetStringData() == TEST_STR_THREE);
	CHECK(str.GetStringData() == s);
}

TEST_CASE("Operator + (std::string with CMyString) test")
{
	cout << "Operator + (std::string with CMyString) test started" << endl;
	CMyString myStr = "pizza";
	CMyString myStr1;
	string str = "qwerty";
	string str1 = "";
	myStr = str + myStr;
	myStr = str1 + myStr;
	myStr1 = str1 + myStr1;
	CHECK(myStr1.GetStringData() == EMPTY_STR);
	myStr1 = str + myStr1;
	CHECK(myStr.GetStringData() == TEST_STR_THREE);
	CHECK(myStr1.GetStringData() == TEST_STR_ONE);
}

TEST_CASE("Operator + (const char* with CMyString) test")
{
	cout << "Operator + (const char* with CMyString) test started" << endl;
	CMyString myStr = "pizza";
	myStr = myStr + "qwerty";
	CHECK(myStr.GetStringData() == TEST_STR_THREE);
	myStr.Clear();
	myStr = myStr + "pizza";
	CHECK(myStr.GetStringData() == TEST_STR_TWO);
	myStr = "qwerty" + myStr;
	CHECK(myStr.GetStringData() == TEST_STR_THREE);
	CHECK(myStr.GetLength() == 11);
}

TEST_CASE("Operator [] for read test")
{
	cout << "Operator [] for read test started" << endl;
	CMyString myStr = "pizza";
	CMyString myStr1;
	string exceptionResutl;
	char symbol;
	CHECK(myStr[0] == 'p');
	CHECK(myStr[1] == 'i');
	CHECK(myStr[2] == 'z');
	CHECK(myStr[3] == 'z');
	CHECK(myStr[4] == 'a');
	try
	{
		symbol = myStr1[12];
	}
	catch (std::out_of_range const& e)
	{
		exceptionResutl = e.what();
	}
	CHECK(exceptionResutl == OUT_OF_RANGE_EXCEPTION);
	try
	{
		symbol = myStr[12];
	}
	catch (std::out_of_range const& e)
	{
		exceptionResutl = e.what();
	}
	CHECK(exceptionResutl == OUT_OF_RANGE_EXCEPTION);
}

TEST_CASE("Operator [] for write test")
{
	cout << "Operator [] for write test started" << endl;
	CMyString myStr("qwerty");
	string excpResult;
	try
	{
		myStr[12] = 'p';
	}
	catch (std::out_of_range const& e)
	{
		excpResult = e.what();
	}
	myStr[0] = 'p';
	myStr[1] = 'i';
	myStr[2] = 'z';
	myStr[3] = 'z';
	myStr[4] = 'a';
	CHECK(myStr[0] == 'p');
	CHECK(myStr[1] == 'i');
	CHECK(myStr[2] == 'z');
	CHECK(myStr[3] == 'z');
	CHECK(myStr[4] == 'a');
	CHECK(excpResult == OUT_OF_RANGE_EXCEPTION);
}

TEST_CASE("Operator < tests")
{
	cout << "Operator < tests started" << endl;
	CMyString myStr("abc");
	CMyString myStr1("aaa");
	CMyString myStr2("qwerty");
	CMyString myStr3;
	CMyString myStr4("aa");
	CHECK((myStr1 < myStr) == true);
	CHECK((myStr3 < myStr2) == true);
	CHECK((myStr4 < myStr1) == true);
	CHECK((myStr < myStr2) == true);
	CHECK((myStr1 < myStr1) == false);
}

TEST_CASE("Operator > tests")
{
	cout << "Operator > tests started" << endl;
	CMyString myStr("abc");
	CMyString myStr1("aaa");
	CMyString myStr2("qwerty");
	CMyString myStr3;
	CMyString myStr4("aa");
	CHECK((myStr > myStr1) == true);
	CHECK((myStr2 > myStr3) == true);
	CHECK((myStr1 > myStr4) == true);
	CHECK((myStr2 > myStr) == true);
	CHECK((myStr1 > myStr1) == false);

}

TEST_CASE("Operator <= tests")
{
	cout << "Operator <= tests started" << endl;
	CMyString myStr("abc");
	CMyString myStr1("aaa");
	CMyString myStr2("qwerty");
	CMyString myStr3;
	CMyString myStr4("aa");
	CMyString myStr5("aaa");
	CHECK((myStr1 <= myStr) == true);
	CHECK((myStr3 <= myStr2) == true);
	CHECK((myStr4 <= myStr1) == true);
	CHECK((myStr <= myStr2) == true);
	CHECK((myStr1 <= myStr1) == true);
	CHECK((myStr5 <= myStr1) == true);
}

TEST_CASE("Operator >= tests")
{
	cout << "Operator >= tests started" << endl;
	CMyString myStr("abc");
	CMyString myStr1("aaa");
	CMyString myStr2("qwerty");
	CMyString myStr3;
	CMyString myStr4("aa");
	CMyString myStr5("aaa");
	CHECK((myStr >= myStr1) == true);
	CHECK((myStr2 >= myStr3) == true);
	CHECK((myStr1 >= myStr4) == true);
	CHECK((myStr2 >= myStr) == true);
	CHECK((myStr1 >= myStr1) == true);
	CHECK((myStr5 >= myStr1) == true);
}

TEST_CASE("Operator << tests")
{
	cout << "Operator << tests started" << endl;
	CMyString myStr;
	CMyString myStr1("aaa");
	CMyString myStr2("qwerty");
	ostringstream oStream;
	oStream << myStr2.GetStringData();
	CHECK(oStream.str() == "qwerty");
	oStream.clear();
	oStream << myStr.GetStringData();
	CHECK(oStream.str() == "qwerty");
	oStream.clear();
	oStream << myStr1.GetStringData();
	CHECK(oStream.str() == "qwertyaaa");
}

TEST_CASE("Operator >> tests")
{
	cout << "Operator >> tests started" << endl;
	string testStr1 = "qwerty";
	string testStr2 = "penpineappleapplepen";
	istringstream iStream1(testStr1);
	istringstream iStream2(testStr2);
	CMyString myStr1;
	iStream1 >> myStr1;
	CMyString myStr2;
	iStream2 >> myStr2;
	CHECK(myStr2 == CMyString("penpineappleapplepen"));
}

TEST_CASE("Operator SubString tests")
{
	cout << "Operator SubString tests started" << endl;
	CMyString MyStr1("pizzaqwerty");
	CMyString MyStr2("pizza/0qwerty", 12);

	string excpResult;
	CHECK(MyStr1.SubString(1, 5) == CMyString("pizza"));
	try
	{
		MyStr1.SubString(1, 15);
	}
	catch (std::out_of_range const& e)
	{
		excpResult = e.what();
	}
	CHECK(excpResult == OUT_OF_LENGTH);
	try
	{
		MyStr1.SubString(1, 12);
	}
	catch (std::out_of_range const& e)
	{
		excpResult = e.what();
	}
	CHECK(excpResult == OUT_OF_LENGTH);
	try
	{
		MyStr1.SubString(2, 11);
	}
	catch (std::out_of_range const& e)
	{
		excpResult = e.what();
	}
	CHECK(excpResult == OUT_OF_LENGTH);
	CHECK(MyStr1.SubString(1, 5) == CMyString("pizza"));
	CHECK(MyStr1.SubString(1, 11) == CMyString("pizzaqwerty"));
	CHECK(MyStr1.SubString(11, 1) == CMyString("y"));
	CHECK(MyStr1.SubString(5, 4) == CMyString("aqwe"));
	CHECK(MyStr2.SubString(1, 12) == CMyString("pizza/0qwerty", 12));
	CHECK(MyStr2.SubString(1, 6) == CMyString("pizza/0", 6));
	CHECK(MyStr2.SubString(1, 7) == CMyString("pizza/0q", 7));
}