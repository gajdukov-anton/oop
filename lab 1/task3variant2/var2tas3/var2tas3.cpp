// var2tas3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

double FindMatrixDeterminat(double mat[3][3]);
double FindElementOfMatrixOfAddition(double mat[3][3], int ElemX, int ElemY);

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("You need enter argument for correct work.\n");
		return 0;
	}

	ifstream input_file(argv[1]);

	if (!input_file.is_open())
	{
		cout << "File is not find, please check your data and repeat again.\n";
		return 1;
	}

	double matrix[3][3];
	double matrixOfAddition[3][3];
	double inverseMatrix[3][3];
	double determinat;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			input_file >> matrix[i][j];
		}

	}

	determinat = FindMatrixDeterminat(matrix);

	if (determinat == 0)
	{
		cout << "Determinat is less then zero. Inverse Matrix is not available. \n";
		return 0;
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrixOfAddition[i][j] = FindElementOfMatrixOfAddition(matrix, j, i);
		}
	}
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			inverseMatrix[i][j] = matrixOfAddition[j][i] / determinat;
			printf("%.3f", inverseMatrix[i][j]);
			cout << ' ';
		}
		cout << endl;
	}

	input_file.close();
    return 0;
}

double FindMatrixDeterminat(double mat[3][3])
{
	double result = 0;
	double paramOne;
	double paramTwo;
	paramOne = mat[0][0] * mat[1][1] * mat[2][2] + mat[0][1] * mat[1][2] * mat[2][0] + mat[0][2] * mat[1][0] * mat[2][1];
	paramTwo = mat[0][2] * mat[1][1] * mat[2][0] + mat[0][1] * mat[1][0] * mat[2][2] + mat[0][0] * mat[1][2] * mat[2][1];
	result = paramOne - paramTwo;
	return result;
}

double FindElementOfMatrixOfAddition(double mat[3][3], int minorCoordinateX, int minorCoordinateY)
{
	double minor[2][2];
	double result = 0;
	int matrixOfAdditionCoordinateX = 0;
	int matrixOfAdditionCoordinateY = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (i != minorCoordinateY && j != minorCoordinateX)
			{
				minor[matrixOfAdditionCoordinateY][matrixOfAdditionCoordinateX] = mat[i][j];
				++matrixOfAdditionCoordinateX;
			}
			if (matrixOfAdditionCoordinateX == 2)
			{
				matrixOfAdditionCoordinateX = 0;
				++matrixOfAdditionCoordinateY;
			}
		}
	}

	int multiplier = 1;
	if ((minorCoordinateY + minorCoordinateX) % 2 != 0)
		multiplier = -1;
	result = multiplier * (minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0]);

	return result;
}