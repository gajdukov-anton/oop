#include "stdafx.h"
#include <iostream>
#include <boost/chrono.hpp>


int main(int argc, _TCHAR* argv[])
{
	std::cout << boost::chrono::steady_clock::now() << std::endl;
	return 0;
}

