// testString.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../string/CMyString.h"
#include <iostream>
#include <string>

using namespace std;

const string TEST_STR_ONE = "qwerty";
const string EMPTY_STR = "";
const string TEST_STR_TWO = "pizza";
const string TEST_STR_THREE = "pizzaqwerty";

TEST_CASE("CMyString constructor test")
{
	cout << "Constructor tests started" << endl;
	string strResult;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	CHECK(str.GetLength() == 6);
	CHECK(str1.GetLength() == 5);
	CHECK(str.GetStringData() == TEST_STR_ONE);
	CHECK(str1.GetStringData() == TEST_STR_TWO);
}

TEST_CASE("Clear function test")
{
	cout << "Clear function tests started" << endl;
	CMyString str("qwerty");
	CMyString str1("pizza", 5);
	str.Clear();
	CHECK(str.GetStringData() == EMPTY_STR);
	CHECK(str.GetLength() == 0);
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