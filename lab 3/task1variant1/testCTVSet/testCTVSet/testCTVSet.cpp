// testCTVSet.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../TV/TV/CTVSet.h"
#include <string>


TEST_CASE("TurnOn test")
{
	CTVSet tv;
	CHECK(tv.TurnOn() == true);
	CHECK(tv.TurnOn() == false);

}

TEST_CASE("TurnOff test")
{
	CTVSet tv;
	CHECK(tv.TurnOff() == false);
	tv.TurnOn();
	CHECK(tv.TurnOff() == true);

}

TEST_CASE("SelectChannel test")
{
	CTVSet tv;
	CHECK(tv.SelectChannel(9) == 0);
	tv.TurnOn();
	CHECK(tv.SelectChannel(0) == 0);
	CHECK(tv.SelectChannel(9) == 9);
	CHECK(tv.SelectChannel(100) == 0);
	tv.TurnOff();
	CHECK(tv.SelectChannel(9) == 0);
}

TEST_CASE("info test")
{
	CTVSet tv;
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	tv.TurnOn();
	CHECK(tv.info() == "The TV is on, current chanel: 1");
	tv.SelectChannel(0);
	CHECK(tv.info() == "The TV is on, current chanel: 1");
	tv.SelectChannel(9);
	CHECK(tv.info() == "The TV is on, current chanel: 9");
	tv.SelectChannel(99);
	CHECK(tv.info() == "The TV is on, current chanel: 99");
	tv.TurnOff();
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	tv.TurnOn();
	CHECK(tv.info() == "The TV is on, current chanel: 99");
}

