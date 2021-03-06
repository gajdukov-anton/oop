// url.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main()
{
	string strUrl;
	while (getline(cin, strUrl))
	{
		try
		{
			CHttpUrl url(strUrl);
			cout << "Url: " << url.GetUrl() << endl;
			cout << "Protocol: " << url.GetStrProtocol() << endl;
			cout << "Domain: " << url.GetDomain() << endl;
			cout << "Port: " << url.GetPort() << endl;
			cout << "Document: " << url.GetDocument() << endl;
		}
		catch (CUrlParsingError error)
		{
			cout << error.GetMessage() << endl;
		}
	}
    return 0;
}

