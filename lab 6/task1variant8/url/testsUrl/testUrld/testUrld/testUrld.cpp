// testUrld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../url/CHttpUrl.h"
#include "../../../url/CommandForParsing.h"
#include "../../../url/CUrlParsingError.h"


using namespace std;

const string INVALID_DOMAIN_EXCEPTION = "Invalid type of Domain.";
const string INVALID_DOCUMENT_EXCEPTION = "Invalid type of Document.";
const string INVALID_PROTOCOL_EXCEPTION = "Invalid type of Protocol.";
const string INVALID_PORT_EXCEPTION = "Invalid value of port.";
const string INVALID_URL = "Invalid url";
const string EMPTY_URL = "Url is empty";

TEST_CASE("CreateProtocol tests (valid value)")
{
	cout << "CreateProtocol tests (valid value) started" << endl;
	CHttpUrl testUrl;
	testUrl.CreateProtocol("https");
	CHECK(testUrl.GetProtocol() == HTTPS);
	testUrl.CreateProtocol("http");
	CHECK(testUrl.GetProtocol() == HTTP);
}

TEST_CASE("CreateDocument tests")
{
	cout << "CreateDocument tests started" << endl;
	CHttpUrl testUrl;
	testUrl.CreateDocument("main/index.html");
	CHECK(testUrl.GetDocument() == "/main/index.html");
	testUrl.CreateDocument("");
	CHECK(testUrl.GetDocument() == "/");

}

TEST_CASE("CreateProtocol tests (invalid value)")
{
	cout << "CreateProtocol tests (invalid value) started" << endl;
	CHttpUrl testUrl;
	try
	{
		testUrl.CreateProtocol("htttp");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		testUrl.CreateProtocol("hhttp");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		testUrl.CreateProtocol("httpss");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		testUrl.CreateProtocol("");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
}

TEST_CASE("CreatePort test (valid value)")
{
	cout << "CreatePort tests (valid value) started" << endl;
	CHttpUrl testUrl;
	testUrl.CreatePort("180");
	CHECK(testUrl.GetPort() == 180);
	testUrl.CreatePort("80");
	CHECK(testUrl.GetPort() == 80);
}

TEST_CASE("CreatePort test (invalid value)")
{
	cout << "CreatePort tests (invalid value) started" << endl;
	CHttpUrl testUrl;
	try
	{
		testUrl.CreatePort("");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PORT_EXCEPTION);
	}
	try
	{
		testUrl.CreatePort("20000000000");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PORT_EXCEPTION);
	}
}

TEST_CASE("CreateDomain tests (valid value)")
{
	cout << "CreateProtocol tests (valid value) started" << endl;
	CHttpUrl testUrl;
	testUrl.CreateDomain("www.google.com");
	CHECK(testUrl.GetDomain() == "www.google.com");
	testUrl.CreateDomain("otvet.mail.ru");
	CHECK(testUrl.GetDomain() == "otvet.mail.ru");
	testUrl.CreateDomain("vk.com");
	CHECK(testUrl.GetDomain() == "vk.com");
}

TEST_CASE("CreateDomain tests (invalid value)")
{
	cout << "CreateDomain tests (invalid value) started" << endl;
	CHttpUrl testUrl;
	try
	{
		testUrl.CreateDomain("www.goo?%gle.com");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		testUrl.CreateDomain("www.yand!ex.ru");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		testUrl.CreateDomain("w..ww.yandex.ru");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_DOMAIN_EXCEPTION);
	}
}

TEST_CASE("Constructor with only string tests(valid values)")
{
	cout << "Constructor with only string tests(valid values) started" << endl;
	string testStr1 = "http://www.google.com:80/index.html";
	string testStr2 = "https://www.google.com:443/main/index.html";
	string testStr3 = "https://www.yandex.ru:443/main/index.html";
	CHttpUrl testUrl1(testStr1);
	CHttpUrl testUrl2(testStr2);
	CHttpUrl testUrl3(testStr3);
	CHECK(testUrl1.GetDomain() == "www.google.com");
	CHECK(testUrl1.GetDocument() == "/index.html");
	CHECK(testUrl1.GetProtocol() == HTTP);
	CHECK(testUrl1.GetPort() == 80);
	CHECK(testUrl2.GetDomain() == "www.google.com");
	CHECK(testUrl2.GetDocument() == "/main/index.html");
	CHECK(testUrl2.GetProtocol() == HTTPS);
	CHECK(testUrl2.GetPort() == 443);
	CHECK(testUrl3.GetDomain() == "www.yandex.ru");
	CHECK(testUrl3.GetDocument() == "/main/index.html");
	CHECK(testUrl3.GetProtocol() == HTTPS);
	CHECK(testUrl3.GetPort() == 443);
}

TEST_CASE("Constructor with only string tests(invalid values)")
{
	cout << "Constructor with only string tests(invalid values) started" << endl;
	try
	{
		CHttpUrl testUrl("htttp://www.google.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl("httpp://www.google.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl("pp://www.google.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PROTOCOL_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl("://www.google.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_URL);
	}
	try
	{
		CHttpUrl testUrl("ajcbajhhvabbvavvac");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_URL);
	}
	try
	{
		CHttpUrl testUrl("http://www.go!ogle.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_URL);
	}
	try
	{
		CHttpUrl testUrl("http://www.go...ogle.com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl("http://www.go.ogle..com:80/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl("http://www.google.com:0/index.html");
	}
	catch (CUrlParsingError error)
	{
		CHECK(error.GetMessage() == INVALID_PORT_EXCEPTION);
	}
}

TEST_CASE("Constructor with domain, protocol, document and port tests(valid values)")
{
	cout << "Constructor with domain, protocol, document and port tests(valid values) started" << endl;
	CHttpUrl testUrl1("www.google.com", "index.html", HTTP, 80);
	CHttpUrl testUrl2("www.yandex.com", "main/index.html", HTTPS, 443);
	CHECK(testUrl1.GetDocument() == "/index.html");
	CHECK(testUrl1.GetProtocol() == HTTP);
	CHECK(testUrl1.GetDomain() == "www.google.com");
	CHECK(testUrl1.GetPort() == 80);
	CHECK(testUrl1.GetUrl() == "http://www.google.com:80/index.html");
	CHECK(testUrl2.GetDocument() == "/main/index.html");
	CHECK(testUrl2.GetProtocol() == HTTPS);
	CHECK(testUrl2.GetDomain() == "www.yandex.com");
	CHECK(testUrl2.GetPort() == 443);
	CHECK(testUrl2.GetUrl() == "https://www.yandex.com:443/main/index.html");
}

TEST_CASE("Constructor with domain, protocol, document and port tests(invalid values)")
{
	cout << "Constructor with domain, protocol, document and port tests(invalid values) started" << endl;
	try
	{
		CHttpUrl testUrl1("www.g%@&&^#*#oogle.com", "index.html", HTTP, 80);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("www.g@*oogle.com", "index.html", HTTP, 80);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("www.google.com", "index.html", HTTP, 0);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_PORT_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("www.google.com", "index.html", HTTP, 2000000000);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_PORT_EXCEPTION);
	}
}

TEST_CASE("Constructor with domain, protocol, document tests(valid values)")
{
	cout << "Constructor with domain, protocol, document tests(valid values) started" << endl;
	CHttpUrl testUrl1("www.google.com", "index.html", HTTP);
	CHttpUrl testUrl2("www.yandex.com", "main/index.html", HTTPS);
	CHECK(testUrl1.GetDocument() == "/index.html");
	CHECK(testUrl1.GetProtocol() == HTTP);
	CHECK(testUrl1.GetDomain() == "www.google.com");
	CHECK(testUrl1.GetPort() == 80);
	CHECK(testUrl1.GetUrl() == "http://www.google.com:80/index.html");
	CHECK(testUrl2.GetDocument() == "/main/index.html");
	CHECK(testUrl2.GetProtocol() == HTTPS);
	CHECK(testUrl2.GetDomain() == "www.yandex.com");
	CHECK(testUrl2.GetPort() == 443);
	CHECK(testUrl2.GetUrl() == "https://www.yandex.com:443/main/index.html");
}

TEST_CASE("Constructor with domain, protocol, document tests(invalid values)")
{
	cout << "Constructor with domain, protocol, document tests(invalid values) started" << endl;
	try
	{
		CHttpUrl testUrl1("www.g%@&&^#*#oogle.com", "index.html", HTTP);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("www.g@*oogle.com", "index.html", HTTP);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("www.g...oogle.com", "index.html", HTTP);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
	try
	{
		CHttpUrl testUrl1("", "index.html", HTTP);
	}
	catch (invalid_argument error)
	{
		CHECK(error.what() == INVALID_DOMAIN_EXCEPTION);
	}
}