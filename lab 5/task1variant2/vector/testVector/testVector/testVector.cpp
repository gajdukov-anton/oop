// testVector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../vector/CVector3D.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

const double EPSILON = 0.001;

bool CompareDoubles2(double A, double B);
bool CompaireFiles(ifstream& file1, ifstream& file2);

TEST_CASE("GetLenght test")
{
	cout << "GetLength test started" << endl;
	CVector3D vector1;
	CVector3D vector2(3, 4, 0);
	double x;
	double y;
	double z;
	CHECK(vector1.GetLength() == 0.0);
	CHECK(vector2.GetLength() == 5.0);
	vector2.Normalize();
	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	CHECK(CompareDoubles2(x, 0.6) == true);
	CHECK(CompareDoubles2(y, 0.8) == true);
	CHECK(CompareDoubles2(z, 0.0) == true);
}

TEST_CASE("Opearation binary + test")
{
	cout << "Opearation binary + test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = vector1 + vector2;
	vector2 = vector2 + vector3;
	CHECK(vector3.x == 47.0);
	CHECK(vector3.y == 26.0);
	CHECK(vector3.z == 5.0);
	CHECK(vector2.x == 92.0);
	CHECK(vector2.y == 49.0);
	CHECK(vector2.z == 6.0);
}

TEST_CASE("Opearation binary - test")
{
	cout << "Opearation binary - test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = vector1 - vector2;
	vector2 = vector2 - vector3;
	CHECK(vector3.x == -43.0);
	CHECK(vector3.y == -20.0);
	CHECK(vector3.z == 3.0);
	CHECK(vector2.x == 88.0);
	CHECK(vector2.y == 43.0);
	CHECK(vector2.z == -2.0);
}

TEST_CASE("Opearation / test")
{
	cout << "Operation / test started" << endl;
	ofstream outFile("divByZero.txt");
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = vector1 / 12.0;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, 0.166) == true);
	CHECK(CompareDoubles2(y, 0.25) == true);
	CHECK(CompareDoubles2(z, 0.333) == true);
	vector3 = vector2 / 12.0;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	try
	{
		vector1 = vector1 / 0.0;
	}
	catch (std::invalid_argument const& e)
	{
		outFile << "Error: " << e.what() << "\n";
	}
	outFile.close();
	ifstream result("divByZero.txt");
	ifstream example("resultDivByZero1.txt");
	CHECK(CompaireFiles(result, example));
	CHECK(CompareDoubles2(x, 3.75) == true);
	CHECK(CompareDoubles2(y, 1.916) == true);
	CHECK(CompareDoubles2(z, 0.083) == true);
}

TEST_CASE("Operator * by scalar test")
{
	cout << "Operator * by scalar test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = vector1 * 25.6;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, 51.2) == true);
	CHECK(CompareDoubles2(y, 76.8) == true);
	CHECK(CompareDoubles2(z, 102.4) == true);
	vector3 = vector2 * 24.0;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 1080.0) == true);
	CHECK(CompareDoubles2(y, 552.0) == true);
	CHECK(CompareDoubles2(z, 24.0) == true);
}

TEST_CASE("Operator * by vector test")
{
	cout << "Operator * by vector test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 =  25.6 * vector1;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, 51.2) == true);
	CHECK(CompareDoubles2(y, 76.8) == true);
	CHECK(CompareDoubles2(z, 102.4) == true);
	vector3 = 24.0 * vector2;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 1080.0) == true);
	CHECK(CompareDoubles2(y, 552.0) == true);
	CHECK(CompareDoubles2(z, 24.0) == true);
}

TEST_CASE("Operator += test")
{
	cout << "Operator += test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 += vector1;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, 2.0) == true);
	CHECK(CompareDoubles2(y, 3.0) == true);
	CHECK(CompareDoubles2(z, 4.0) == true);
	vector3 += vector2;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 47.0) == true);
	CHECK(CompareDoubles2(y, 26.0) == true);
	CHECK(CompareDoubles2(z, 5.0) == true);
	vector3 += vector3;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 94.0) == true);
	CHECK(CompareDoubles2(y, 52.0) == true);
	CHECK(CompareDoubles2(z, 10.0) == true);
}

TEST_CASE("Opearator -= test")
{
	cout << "Operator -= test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 -= vector1;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, -2.0) == true);
	CHECK(CompareDoubles2(y, -3.0) == true);
	CHECK(CompareDoubles2(z, -4.0) == true);
	vector3 -= vector2;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, -47.0) == true);
	CHECK(CompareDoubles2(y, -26.0) == true);
	CHECK(CompareDoubles2(z, -5.0) == true);
	vector3 -= vector3;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 0.0) == true);
	CHECK(CompareDoubles2(y, 0.0) == true);
	CHECK(CompareDoubles2(z, 0.0) == true);
}

TEST_CASE("Operator *= test")
{
	cout << "Operator *= test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	vector1 *= 12.0;
	double x = vector1.x;
	double y = vector1.y;
	double z = vector1.z;
	CHECK(CompareDoubles2(x, 24.0) == true);
	CHECK(CompareDoubles2(y, 36.0) == true);
	CHECK(CompareDoubles2(z, 48.0) == true);
	vector2 *= 19.34;
	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	CHECK(CompareDoubles2(x, 870.3) == true);
	CHECK(CompareDoubles2(y, 444.82) == true);
	CHECK(CompareDoubles2(z, 19.34) == true);
}

TEST_CASE("Operator /= test")
{
	cout << "Operator /= test started" << endl;
	ofstream outFile("divByZero.txt");
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	vector1 /= 12.0;
	double x = vector1.x;
	double y = vector1.y;
	double z = vector1.z;
	CHECK(CompareDoubles2(x, 0.166) == true);
	CHECK(CompareDoubles2(y, 0.25) == true);
	CHECK(CompareDoubles2(z, 0.333) == true);
	vector2 /= 19.34;
	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	try
	{
		vector1 = vector1 / 0.0;
	}
	catch (std::invalid_argument const& e)
	{
		outFile << "Error: " << e.what() << "\n";
	}
	outFile.close();
	ifstream result("divByZero.txt");
	ifstream example("resultDivByZero1.txt");
	CHECK(CompaireFiles(result, example));
	CHECK(CompareDoubles2(x, 2.326) == true);
	CHECK(CompareDoubles2(y, 1.189) == true);
	CHECK(CompareDoubles2(z, 0.051) == true);
}

TEST_CASE("Opearator unary - test")
{
	cout << "Operator unary - test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = -vector1;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, -2.0) == true);
	CHECK(CompareDoubles2(y, -3.0) == true);
	CHECK(CompareDoubles2(z, -4.0) == true);
	vector3 = -vector2;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, -45.0) == true);
	CHECK(CompareDoubles2(y, -23.0) == true);
	CHECK(CompareDoubles2(z, -1.0) == true);
	vector3 = -vector3;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 45.0) == true);
	CHECK(CompareDoubles2(y, 23.0) == true);
	CHECK(CompareDoubles2(z, 1.0) == true);
}

TEST_CASE("Opearator unary + test")
{
	cout << "Operator unary + test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	vector3 = +vector1;
	double x = vector3.x;
	double y = vector3.y;
	double z = vector3.z;
	CHECK(CompareDoubles2(x, 2.0) == true);
	CHECK(CompareDoubles2(y, 3.0) == true);
	CHECK(CompareDoubles2(z, 4.0) == true);
	vector3 = +vector2;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 45.0) == true);
	CHECK(CompareDoubles2(y, 23.0) == true);
	CHECK(CompareDoubles2(z, 1.0) == true);
	vector3 = +vector3;
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	CHECK(CompareDoubles2(x, 45.0) == true);
	CHECK(CompareDoubles2(y, 23.0) == true);
	CHECK(CompareDoubles2(z, 1.0) == true);
}

TEST_CASE("Operator != test")
{
	cout << "Operator != test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(45, 23, 1);
	CVector3D vector3;
	CVector3D vector4(0, 0, 1);
	CHECK(vector1 != vector2);
	CHECK(vector1 != vector3);
	CHECK(vector1 != vector4);
	CHECK(vector2 != vector3);
	CHECK(vector2 != vector4);
	CHECK(vector4 != vector3);
}

TEST_CASE("Operator == test")
{
	cout << "Operator == test started" << endl;
	CVector3D vector1(2, 3, 4);
	CVector3D vector2(2, 3, 4);
	CVector3D vector3;
	CVector3D vector4(0, 0, 0);
	CHECK(vector1 == vector2);
	CHECK(vector3 == vector4);
}

TEST_CASE("Operator << and >> test")
{
	cout << "Operator << and operator >> test started" << endl;
	ifstream inFile("test1.txt");
	ofstream outFile("output.txt");
	CVector3D vector1;
	CVector3D vector2(2, 3, 4);
	inFile >> vector1;
	outFile << vector2 << endl;
	outFile << vector1 << endl;
	inFile >> vector1;
	outFile << vector1;
	outFile.close();
	ifstream result("output.txt");
	ifstream example("result1.txt");
	CHECK(CompaireFiles(result, example) == true);
}

TEST_CASE("Normalize test")
{
	cout << "Normalize test started" << endl;
	CVector3D vector1;
	CVector3D vector2(3, 4, 0);
	vector1 = Normalize(vector2);
	double x = vector1.x;
	double y = vector1.y;
	double z = vector1.z;
	CHECK(CompareDoubles2(x, 0.6) == true);
	CHECK(CompareDoubles2(y, 0.8) == true);
	CHECK(CompareDoubles2(z, 0.0) == true);
}

TEST_CASE("CrossProduct test")
{
	cout << "CrossProdut test started" << endl;
	CVector3D vector1(2, 2, 2);
	CVector3D vector2(1, 2, 2);
	CVector3D vector3 = CrossProduct(vector1, vector2);
	CHECK(vector3 == CVector3D(0, -2, 2));
}

TEST_CASE("DotProduct test")
{
	cout << "DotProduct test started" << endl;
	CVector3D vector1(0, 3, 4);
	CVector3D vector2(0.0, 0.6, 0.8);
	double resultDorProduct = DotProduct(vector1, vector2);
	CHECK(resultDorProduct == 5.0);
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



bool CompareDoubles2(double A, double B)
{
	double diff = A - B;
	return (diff < EPSILON) && (-diff < EPSILON);
}

