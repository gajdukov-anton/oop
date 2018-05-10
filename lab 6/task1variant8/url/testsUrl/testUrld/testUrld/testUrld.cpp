// testUrld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../url/CHttpUrl.h"
#include "../../../url/CommandForParsing.h"
#include "../../../url/CUrlParsingError.h"
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

TEST_CASE("CheckDomain tests")
{
	cout << "CheckDomain tests started" << endl;
	string testDomain1 = "www.google.com";
	string testDomain2 = "ww.google.com";
	string testDomain3 = "wwwgoogle.com";
	string testDomain4 = "www.googlecom";
	string testDomain5 = "www..com";
	string testDomain6 = "www";
	string testDomain7 = ".com";
	string testDomain8 = "www.";
	CHECK(CheckDomain(testDomain1) == true);
	CHECK(CheckDomain(testDomain2) == false);
	CHECK(CheckDomain(testDomain3) == false);
	CHECK(CheckDomain(testDomain4) == false);
	CHECK(CheckDomain(testDomain5) == false);
	CHECK(CheckDomain(testDomain6) == false);
	CHECK(CheckDomain(testDomain7) == false);
	CHECK(CheckDomain(testDomain8) == false);
}

TEST_CASE("CheckDocument tests")
{
	cout << "CheckDocument tests started" << endl;
	string testDocument1 = "/index.html";
	string testDocument2 = "/";
	string testDocument3 = "";
	string testDocument4 = "//inde.html";
	string testDocument5 = "index.html";
	CHECK(CheckDocument(testDocument1) == true);
	CHECK(CheckDocument(testDocument2) == false);
	CHECK(CheckDocument(testDocument3) == false);
	CHECK(CheckDocument(testDocument4) == false);
	CHECK(CheckDocument(testDocument5) == false);
}

TEST_CASE("GetDomainFromUrl tests")
{
	cout << "GetDomainFromUrl tests started" << endl;
	string testStr1 = "http://www.google.com/";
	string testStr2 = "https://www.google.com/index.htlm";
	string testStr3 = "http://wwwgoogle.com/index.html";
	string testStr4 = "http://ww.google.com/index.html";
	string testStr5 = "http://wwwgooglecom/index.htm;";
	string testStr6 = "http://wwwcom/index.html";
	string testStr7 = "http://www.google.com/";
	string testStr8 = "http://www..com/index.html";
	string testStr9 = "http://www.com/index.html";
	size_t pos = 6;
	CHECK(GetDomainFromUrl(testStr1, 7, pos) == "www.google.com");
	CHECK(pos == 21);
	CHECK(GetDomainFromUrl(testStr2, 8, pos) == "www.google.com");
	CHECK(pos == 22);
	CHECK(GetDomainFromUrl(testStr3, 7, pos) == "");
	CHECK(GetDomainFromUrl(testStr4, 7, pos) == "");
	CHECK(GetDomainFromUrl(testStr5, 7, pos) == "");
	CHECK(GetDomainFromUrl(testStr6, 7, pos) == "");
	CHECK(GetDomainFromUrl(testStr7, 7, pos) == "www.google.com");
	CHECK(GetDomainFromUrl(testStr8, 7, pos) == "");
	CHECK(GetDomainFromUrl(testStr9, 7, pos) == "");
}

TEST_CASE("GetDocumentFromUrl tests")
{
	cout << "GetDocumentFromUrl tests started" << endl;
	string testStr1 = "http://www.google.com/index.html";
	string testStr2 = "https://www.google.com/main/index.html";
	string testStr3 = "http://www.google.com/";
	CHECK(GetDocumentFromUrl(testStr2, 22) == "/main/index.html");
	CHECK(GetDocumentFromUrl(testStr1, 21) == "/index.html");
	CHECK(GetDocumentFromUrl(testStr3, 21) == "");
}

TEST_CASE("GetProtocol tests")
{
	cout << "GetProtocol tests started" << endl;
	string testStr1 = "http://www.google.com/index.html";
	string testStr2 = "https://www.google.com/index.html";
	string testStr3 = "httpss://www.google.com/index.html";
	string testStr4 = "https:/www.google.com/index.html";
	string testStr5 = "https:://www.google.com/index.html";
	size_t pos;
	CHECK(GetProtocolFromUrl(testStr1, pos) == "http");
	CHECK(pos == 6);
	CHECK(GetProtocolFromUrl(testStr2, pos) == "https");
	CHECK(pos == 7);
	CHECK(GetProtocolFromUrl(testStr3, pos) == "");
	CHECK(GetProtocolFromUrl(testStr4, pos) == "");
	CHECK(GetProtocolFromUrl(testStr5, pos) == "");
}

TEST_CASE("Constructor with only string tests")
{
	cout << "Constructor with only string tests" << endl;
	string testStr1 = "http://www.google.com/index.html";
	string testStr2 = "https://www.google.com/main/index.html";
	string testStr3 = "htp://www.google.com/index.html";
	string testStr4 = "http//www.google.com/index.html";
	CHttpUrl testUrl1(testStr1);
	CHttpUrl testUrl2(testStr2);
	try
	{
		CHttpUrl testUrl3(testStr3);
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == "Invalid type of Protocol.");
	}
	try
	{
		CHttpUrl testUrl4(testStr4);
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == "Invalid type of Protocol.");
	}
	CHECK(testUrl1.GetDomain() == "www.google.com");
	CHECK(testUrl1.GetDocument() == "/index.html");
	CHECK(testUrl1.GetProtocol() == HTTP);
	CHECK(testUrl1.GetPort() == 80);
	CHECK(testUrl2.GetDomain() == "www.google.com");
	CHECK(testUrl2.GetDocument() == "/main/index.html");
	CHECK(testUrl2.GetProtocol() == HTTPS);
	CHECK(testUrl2.GetPort() == 443);
}

TEST_CASE("Constructor with domain, protocol and document tests")
{
	cout << "Constructor with domain, protocol and document tests started" << endl;
	try
	{
		CHttpUrl testUrl("wwwgoogle.com", "index.html", HTTP);
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == "Invalid type of Domain.");
	}
	try
	{
		CHttpUrl testUrl("www.google.com", "", HTTP);
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == "Invalid type of Document.");
	}
	try
	{
		CHttpUrl testUr("www..com", "index.html", HTTP);
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == "Invalid type of Domain.");
	}
}