// testStack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../../CStringStack.h"
#include "../../../CStackError.h"

using namespace std;

const string TEST_STRING_ONE = "qwerty";
const string TEST_STRING_TWO = "pizza";
const string TEST_STRING_THREE = "qwake";
const string POP_EXCEPTION = "it is impossible to remove from empty stack";
const string TOP_EXCEPTION = "it is impossible to get top of empty stack";
const string CHANGE_EXCEPTION = "it is impossible to change top of empty stack";

void FillStack(CStringStack& stack);

TEST_CASE("constructor tests")
{
	cout << "Constructor tests started" << endl;
	CStringStack testStack;
	FillStack(testStack);
	CStringStack testStack2(testStack);
	CHECK(testStack.GetSize() == 4);
	CHECK(testStack2.GetSize() == 4);
	CHECK(testStack.GetTop() == testStack2.GetTop());
	CStringStack testStack3(move(testStack2));
	CHECK(testStack3.GetSize() == 4);
	CHECK(testStack2.GetSize() == 0);
}

TEST_CASE("Push tests")
{
	cout << "Push tests started" << endl;
	CStringStack testStack;
	
	testStack.Push(TEST_STRING_ONE);
	CHECK(testStack.GetTop() == TEST_STRING_ONE);
	testStack.Push(TEST_STRING_THREE);
	testStack.Push(TEST_STRING_TWO);
	CHECK(testStack.GetTop() == TEST_STRING_TWO);
}

TEST_CASE("Pop tests")
{
	cout << "Pop tests started" << endl;
	CStringStack testStack;
	FillStack(testStack);
	
	testStack.Pop();
	CHECK(testStack.GetTop() == TEST_STRING_THREE);
	testStack.Pop();
	CHECK(testStack.GetTop() == TEST_STRING_TWO);
	testStack.Pop();
	CHECK(testStack.GetTop() == TEST_STRING_ONE);
	try
	{
		testStack.Pop();
		testStack.Pop();
	}
	catch (const CStackError& error)
	{
		CHECK(error.GetMessage() == POP_EXCEPTION);
	}
	testStack.Push(TEST_STRING_THREE);
	testStack.Pop();
	CHECK(testStack.GetSize() == 0);
}

TEST_CASE("Clear tests")
{
	cout << "Clear tests started" << endl;
	CStringStack testStack;
	FillStack(testStack);

	testStack.Clear();
	CHECK(testStack.GetSize() == 0);
	try
	{
		testStack.GetTop();
	}
	catch (const CStackError& error)
	{
		CHECK(error.GetMessage() == TOP_EXCEPTION);
	}
}

TEST_CASE("ChangeTop tests")
{
	cout << "ChangeTop tests started" << endl;
	CStringStack testStack;
	CStringStack testStack2;
	FillStack(testStack);

	testStack.ChangeTop(TEST_STRING_TWO);
	CHECK(testStack.GetTop() == TEST_STRING_TWO);
	try
	{
		testStack2.ChangeTop(TEST_STRING_TWO);
	}
	catch (const CStackError& error)
	{
		CHECK(error.GetMessage() == CHANGE_EXCEPTION);
	}
}

void FillStack(CStringStack& stack)
{
	stack.Push(TEST_STRING_ONE);
	stack.Push(TEST_STRING_TWO);
	stack.Push(TEST_STRING_THREE);
	stack.Push(TEST_STRING_ONE + TEST_STRING_ONE);
}