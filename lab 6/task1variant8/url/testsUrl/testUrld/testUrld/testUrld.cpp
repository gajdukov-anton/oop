// testUrld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../url/CHttpUrl.h"
#include "../../../url/CommandForParsing.h"
#include <iostream>
#include <string>

using namespace std;

TEST_CASE("CHttpUrl constructor and main methods tests")
{
	cout << "CHttpUrl constructor and main methods tests started" << endl;
	CHttpUrl testUrl1("www.google.com", "index.html", HTTP);
	CHttpUrl testUrl2("www.yandex.com", "index.html", HTTP, 80);
	CHECK(testUrl1.GetDocument() == "/index.html");
	CHECK(testUrl1.GetProtocol() == HTTP);
	CHECK(testUrl1.GetDomain() == "www.google.com");
	CHECK(testUrl2.GetDocument() == "/index.html");
	CHECK(testUrl2.GetProtocol() == HTTP);
	CHECK(testUrl2.GetDomain() == "www.yandex.com");
	CHECK(testUrl2.GetPort() == 80);
}

TEST_CASE("GetDomainFromUrl tests")
{
	cout << "GetDomainFromUrl tests started" << endl;
	string testStr1 = "//www.google.com/";
	string testStr2 = "//www.google.com/index.htlm";
	string testStr3 = "www.google.com/";
	string testStr4 = "//ww.google.com/";
	string testStr5 = "//wwwgoogle.com/";
	string testStr6 = "//www.googlecom/";
	string testStr7 = "//www.google.com";
	size_t pos;
	CHECK(GetDomainFromUrl(testStr1, pos) == "//www.google.com");
	CHECK(pos == 16);
	CHECK(GetDomainFromUrl(testStr2, pos) == "//www.google.com");
	CHECK(pos == 16);
	CHECK(GetDomainFromUrl(testStr3, pos) == "");
	CHECK(GetDomainFromUrl(testStr4, pos) == "");
	CHECK(GetDomainFromUrl(testStr5, pos) == "");
	CHECK(GetDomainFromUrl(testStr6, pos) == "");
	CHECK(GetDomainFromUrl(testStr7, pos) == "");
}

TEST_CASE("GetDocumentFromUrl tests")
{
	cout << "GetDocumentFromUrl tests started" << endl;
	string testStr1 = "http//www.google.com/index.html";
	string testStr2 = "//www.google.com/index.html";
	string testStr3 = "http//www.google.com/";
	CHECK(GetDocumentFromUrl(testStr2, 16) == "/index.html");
	CHECK(GetDocumentFromUrl(testStr1, 20) == "/index.html");
	CHECK(GetDocumentFromUrl(testStr3, 20) == "");
}