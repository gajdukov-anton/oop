// TestGeometry.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../geometry/geometry/CLineSegment.h"
#include "../../geometry/geometry/СPoint.h"
#include "../../geometry/geometry/CTriangle.h"
#include "../../geometry/geometry/CCircle.h"
#include "../../geometry/geometry/CRectangle.h"
#include "../../geometry/geometry/CommandForCreateShape.h"
#include "../../geometry/geometry/CGeometry.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool CompaireFiles(ifstream& file1, ifstream& file2);

TEST_CASE("CPoint test")
{
	cout << "Start CPoint test" << endl;
	СPoint x(12, 22);
	СPoint y(34, 2.5);
	СPoint z(22, 19.5);	
	CHECK(z.GetX() == 22.0);
	CHECK(z.GetY() == 19.5);
	z = y - x;
	CHECK(z.GetX() == 22.0);
	CHECK(z.GetY() == -19.5);
}

TEST_CASE("CVector test")
{
	cout << "Start CVector test" << endl;
	СPoint x(12, 22);
	СPoint y(34, 2);
	СPoint z(22, 19);
	CVector testVector1(x, y);
	CVector testVector2(y, z);
	CHECK(testVector1.GetX() == y.GetX() - x.GetX());
	CHECK(testVector1.GetY() == y.GetY() - x.GetY());
	CHECK(testVector2.GetX() == z.GetX() - y.GetX());
	CHECK(testVector2.GetY() == z.GetY() - y.GetY());
}


TEST_CASE("CLineSegment test")
{
	cout << "Start CLineSegment test" << endl;
	СPoint x(0, 0);
	СPoint y(10, 0);
	СPoint z(22, 19.5);
	CLineSegment blackLine(x, y);
	CHECK(blackLine.GetArea() == 0);
	CHECK(blackLine.GetPerimeter() == 10.0);
	CHECK(blackLine.GetFinishPoint() == y);
	CHECK(blackLine.GetStartPoint() == x);
	CHECK(blackLine.GetOutlineColor() == "ffffff");
	CLineSegment redLine(y, x, "red");
	CHECK(redLine.GetPerimeter() == 10.0);
	CHECK(redLine.GetArea() == 0);
	CHECK(redLine.GetOutlineColor() == "red");
}

TEST_CASE("CTriangle test")
{
	cout << "Start CTriangle test" << endl;
	СPoint x(0, 0);
	СPoint y(10, 0);
	СPoint z(0, 10);
	CTriangle testTriangle(x, y, z);
	CHECK(testTriangle.GetArea() == 50.0);
	CHECK(testTriangle.GetFillColor() == "ffffff");
	CHECK(testTriangle.GetOutlineColor() == "ffffff");
	CHECK(testTriangle.GetVertex1() == x);
	CHECK(testTriangle.GetVertex2() == y);
	CHECK(testTriangle.GetVertex3() == z);
	CTriangle testTriangle2(x, y, z, "ff00ff", "ff0ff0");
	CHECK(testTriangle2.GetArea() == 50.0);
	CHECK(testTriangle2.GetFillColor() == "ff0ff0");
	CHECK(testTriangle2.GetOutlineColor() == "ff00ff");
	CHECK(testTriangle2.GetVertex1() == x);
	CHECK(testTriangle2.GetVertex2() == y);
	CHECK(testTriangle2.GetVertex3() == z);
	СPoint a(0, 4);
	СPoint b(3, 0);
	СPoint c(0, 0);
	CTriangle testTriangle3(a, b, c);
	CHECK(testTriangle3.GetPerimeter() == 12.0);
	CHECK(testTriangle3.GetArea() == 6.0);
}

TEST_CASE("CCircle test")
{
	cout << "Start CCircle test" << endl;
	СPoint centre1(12, 32);
	СPoint zeroCentre(0, 0);
	CCircle testCircle(centre1, 4.0, "ff00ff", "f0f0f0");
	CHECK(testCircle.GetRadius() == 4.0);
	CHECK(testCircle.GetCentre() == centre1);
	CHECK(testCircle.GetArea() == 50.24);
	CHECK(testCircle.GetPerimeter() == 25.12);
	CHECK(testCircle.GetFillColor() == "f0f0f0");
	CHECK(testCircle.GetOutlineColor() == "ff00ff");
	CCircle circle(centre1, 4.0);
	CHECK(circle.GetOutlineColor() == "ffffff");
	CHECK(circle.GetFillColor() == "ffffff");

}

TEST_CASE("CRectangle test")
{
	cout << "Start CRectangle test" << endl;
	СPoint leftTop(0, 10);
	СPoint rightBottom(10, 0);
	CRectangle testRectangle(leftTop, rightBottom);
	CHECK(testRectangle.GetFillColor() == "ffffff");
	CHECK(testRectangle.GetOutlineColor() == "ffffff");
	CHECK(testRectangle.GetHeight() == 10.0);
	CHECK(testRectangle.GetLeftTop() == leftTop);
	CHECK(testRectangle.GetRightBottom() == rightBottom);
	CHECK(testRectangle.GetWidth() == 10.0);
	CHECK(testRectangle.GetArea() == 100.0);
	CHECK(testRectangle.GetPerimeter() == 40.0);
}


TEST_CASE("CGeometry test")
{
	cout << "Start CGeometry test:" << endl;
	//test #1
	cout << "  Test #1 file with some shapes, comands and invalid comands" << endl;
	ifstream inputFile1("test1.txt");
	ofstream outputFile1("output.txt");
	CGeometry testGeometry1(inputFile1, outputFile1);
	while (!inputFile1.eof())
	{
		testGeometry1.HandleCommand();
	}
	testGeometry1.GetMaxShape();
	testGeometry1.GetMinShape();
	outputFile1.close();
	ifstream result1("result1.txt");
	ifstream outFile1("output.txt");
	CHECK(CompaireFiles(outFile1, result1) == true);
	outputFile1.close();
	//test #2
	cout << "  Test #2 file with only shapes" << endl;
	ifstream inputFile2("test2.txt");
	ofstream outputFile2("output.txt");
	CGeometry testGeometry2(inputFile2, outputFile2);
	while (!inputFile2.eof())
	{
		testGeometry2.HandleCommand();
	}
	testGeometry2.GetMaxShape();
	testGeometry2.GetMinShape();
	outputFile2.close();
	ifstream result2("result2.txt");
	ifstream outFile2("output.txt");
	CHECK(CompaireFiles(outFile2, result2) == true);
	outputFile2.close();
	//test #3
	cout << "  Test #3 file with all shapes and shapes with invalid coordinates" << endl;
	ifstream inputFile3("test3.txt");
	ofstream outputFile3("output.txt");
	CGeometry testGeometry3(inputFile3, outputFile3);
	while (!inputFile3.eof())
	{
		testGeometry3.HandleCommand();
	}
	testGeometry3.GetMaxShape();
	testGeometry3.GetMinShape();
	outputFile3.close();
	ifstream result3("result3.txt");
	ifstream outFile3("output.txt");
	CHECK(CompaireFiles(outFile3, result3) == true);
	outputFile3.close();
	//test #4
	cout << "  Test #4 file with all shapes" << endl;
	ifstream inputFile4("test4.txt");
	ofstream outputFile4("output.txt");
	CGeometry testGeometry4(inputFile4, outputFile4);
	while (!inputFile4.eof())
	{
		testGeometry4.HandleCommand();
	}
	testGeometry4.GetMaxShape();
	testGeometry4.GetMinShape();
	outputFile4.close();
	ifstream result4("result4.txt");
	ifstream outFile4("output.txt");
	CHECK(CompaireFiles(outFile4, result4) == true);
	outputFile4.close();
}

TEST_CASE("StringToDouble test")
{
	CGeometry geometry(cin, cout);
	double number = 0.0;
	CHECK(geometry.StringToDouble("123", number) == true);
	CHECK(number == 123.0);
	CHECK(geometry.StringToDouble("qwert", number) == false);
	CHECK(number == 0.0);
}

bool CompaireFiles(ifstream& file1, ifstream& file2)
{
	char symbolFromFile1;
	char symbolFromFile2;
	while (!file1.eof() || !file2.eof())
	{
		file1.get(symbolFromFile1);
		file2.get(symbolFromFile2);
		if (symbolFromFile1 != symbolFromFile2)
		{
			return false;
		}
	}
	return true;
}