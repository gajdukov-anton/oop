// testCTVSet.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../TV/TV/CTVSet.h"
#include "../../TV/TV/WorkWithCommandr.h"
#include "../../TV/TV/CRemoteControl.h"
#include <string>

using namespace std;

const string COMMAND_TURN_ON = "   TurnOn";
const string COMMAND_TURN_OFF = "TurnOff    ";
const string COMMAND_SELECT_CHANNEL = "   SelectChannel    ";
const string COMMAND_INFO = "info";

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

TEST_CASE("SelectPreviousChannel test")
{
	CTVSet tv;
	CHECK(tv.SelectPreviousChannel() == 0);
	tv.TurnOn();
	CHECK(tv.SelectPreviousChannel() == 1);
	tv.SelectChannel(9);
	CHECK(tv.SelectPreviousChannel() == 1);
	tv.SelectChannel(9);
	CHECK(tv.SelectPreviousChannel() == 1);
	tv.SelectChannel(90);
	tv.SelectChannel(19);
	CHECK(tv.SelectPreviousChannel() == 90);
	tv.TurnOff();
	CHECK(tv.SelectPreviousChannel() == 0);
	tv.TurnOn();
	CHECK(tv.SelectPreviousChannel() == 90);
	tv.SelectChannel(19);
	tv.SelectChannel(9);
	tv.TurnOff();
	tv.TurnOn();
	CHECK(tv.SelectPreviousChannel() == 19);


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
	tv.SelectChannel(199);
	CHECK(tv.info() == "The TV is on, current chanel: 99");
	tv.TurnOff();
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	tv.TurnOn();
	CHECK(tv.info() == "The TV is on, current chanel: 99");
}

TEST_CASE("GetNumberOfChannel test")
{
	CHECK(GetNumberOfChannel("qwerty<1234>", 6) == 1234);
	CHECK(GetNumberOfChannel("SelectChannel<9>", 13) == 9);
	CHECK(GetNumberOfChannel("SelectChanneccccl<9>", 13) == 0);
}

TEST_CASE("CheckCommand test")
{
	CHECK(CheckCommand("SelectChannel<9>") == true);
	CHECK(CheckCommand("SelecttChannel<9>") == false);
	CHECK(CheckCommand("SelectChannell<9>") == false);
	CHECK(CheckCommand("SelectChannel <9>") == false);
	CHECK(CheckCommand("SelectChannel9>") == false);
	CHECK(CheckCommand("Sel") == false);
}

TEST_CASE("RemoveBlanks test")
{
	CHECK(RemoveBlanks(COMMAND_TURN_ON) == "TurnOn");
	CHECK(RemoveBlanks(COMMAND_TURN_OFF) == "TurnOff");
	CHECK(RemoveBlanks(COMMAND_SELECT_CHANNEL) == "SelectChannel");
	CHECK(RemoveBlanks(COMMAND_INFO) == "info");
}

TEST_CASE("HandleCommand test")
{
	CTVSet tv;
	CRemoteControl remoteControl(tv);
	remoteControl.HandleCommand("TurnOn");
	CHECK(tv.info() == "The TV is on, current chanel: 1");
	CHECK(remoteControl.HandleCommand("TurnOn") == true);
	remoteControl.HandleCommand("TurnOff");
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	remoteControl.HandleCommand("TurnOn");
	remoteControl.HandleCommand("SelectChannel<9>");
	CHECK(tv.info() == "The TV is on, current chanel: 9");
	remoteControl.HandleCommand("SelectChannel<99>");
	CHECK(tv.info() == "The TV is on, current chanel: 99");
	remoteControl.HandleCommand("SelectChannel<89>");
	CHECK(tv.info() == "The TV is on, current chanel: 89");
	remoteControl.HandleCommand("SelectChannel<19>");
	CHECK(tv.info() == "The TV is on, current chanel: 19");
	remoteControl.HandleCommand("SelectLastChannel");
	CHECK(tv.info() == "The TV is on, current chanel: 89");
	remoteControl.HandleCommand("SelectChannel<10>");
	CHECK(tv.info() == "The TV is on, current chanel: 10");
	remoteControl.HandleCommand("TurnOff");
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	remoteControl.HandleCommand("TurnOn");
	CHECK(tv.info() == "The TV is on, current chanel: 10");
	remoteControl.HandleCommand("SelectLastChannel");
	CHECK(tv.info() == "The TV is on, current chanel: 89");
	CHECK(remoteControl.HandleCommand("SelectLastChann") == false);
	CHECK(remoteControl.HandleCommand("inf") == false);
	CHECK(remoteControl.HandleCommand("SelectChannel") == false);
	CHECK(remoteControl.HandleCommand("SelectChannel<") == false);
	CHECK(remoteControl.HandleCommand("SelectChannel<p>") == false);
	CHECK(remoteControl.HandleCommand("SelectChannel<9p") == false);
	CHECK(remoteControl.HandleCommand("SelectChannel<9") == false);
	CHECK(remoteControl.HandleCommand("SelectChel<9>") == false);
	CHECK(remoteControl.HandleCommand("SelectChannell<9>") == false);
	remoteControl.HandleCommand("TurnOff");
	remoteControl.HandleCommand("SelectChannel<10>");
	CHECK(tv.info() == "The TV is off, current chanel: 0");
	remoteControl.HandleCommand("TurnOn");
	CHECK(tv.info() == "The TV is on, current chanel: 89");
}