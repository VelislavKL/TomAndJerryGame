#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>

using namespace std;

// създава матрица с информация за нея, взета от текстов файл
Matrix createMatrixFromFile(ifstream &input)
{
	string text;
	int number1;
	int number2;
	int furnNumber; // брой мебели
	int placesForPaint; // брой места, подходящи за разливане с боя
	int furnX; // x координата на мебел
	int furnY; // у координата на мебел

	Matrix m;

	int line = 1; // брояч за редове
	int tempFurnNumber = 0;
	int tempPlacesForPaint = 0;
	int furnLine = 1; // текущ ред на мебел
	while (getline(input, text))
	{
		stringstream ss;
		size_t space = text.find_last_of(" ");

		if (line == 1)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;

			Matrix tempMatrix(number1, number2);
			m = tempMatrix;
		}

		else if (line == 2)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;

			for (int i = 0; i < m.getRows(); i++)
			{
				for (int j = 0; j < m.getColumns(); j++)
				{
					if (i == number1 && j == number2)
						m.setCellValue(i, j, 'J');
				}
			}

		}

		else if (line == 3)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;

			for (int i = 0; i < m.getRows(); i++)
			{
				for (int j = 0; j < m.getColumns(); j++)
				{
					if (i == number1 && j == number2)
						m.setCellValue(i, j, 'T');
				}
			}

		}

		else if (line == 4)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;
			furnNumber = number1;
			placesForPaint = number2;
		}

		else if (text == "===")
		{
			tempFurnNumber++;
			furnLine = 1;
		}

		else if (furnNumber > tempFurnNumber && furnLine == 1)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;
			furnX = number1;
			furnY = number2;
			furnLine++;
		}

		else if (furnNumber > tempFurnNumber && furnLine > 1)
		{
			int tempX = furnX;
			int tempY = furnY;
			for (int i = 0; i < text.size(); i++)
			{
				if (!isspace(text[i]))
				{
					m.setCellValue(tempX, tempY, '1');
				}
				tempY++;
			}
			furnX++;
		}

		else if (furnNumber >= tempFurnNumber && tempPlacesForPaint <= placesForPaint)
		{
			ss.str(text.substr(0));
			ss >> number1;
			ss.str(text.substr(space + 1));
			ss >> number2;
			m.setCellPaint(number1, number2);
			tempPlacesForPaint++;
		}
		line++;
	}
	return m;
}


// достъп до x координата на Jerry в дадена стая
int getJerryX(Matrix m)
{
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getColumns(); j++)
		{
			if (m.getCellValue(i, j) == 'J')
				return i;
		}
	}
	return -1;
}

// достъп до y координата на Jerry в дадена стая
int getJerryY(Matrix m)
{
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getColumns(); j++)
		{
			if (m.getCellValue(i, j) == 'J')
				return j;
		}
	}
	return -1;
}

// достъп до x координата на Tom в дадена стая
int getTomX(Matrix m)
{
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getColumns(); j++)
		{
			if (m.getCellValue(i, j) == 'T')
				return i;
		}
	}
	return -1;
}

// достъп до y координата на Tom в дадена стая
int getTomY(Matrix m)
{
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getColumns(); j++)
		{
			if (m.getCellValue(i, j) == 'T')
				return j;
		}
	}
	return -1;
}

int main()
{
	ifstream input("input.txt");

	if (input.is_open())
	{
		Matrix m = createMatrixFromFile(input);

		if (getTomX(m) != -1 && getTomY(m) != -1 && getJerryX(m) != -1 && getJerryY(m) != -1)
		{

			//m.printMatrix();
			cout << endl;

			m.shortestPaths(getTomX(m), getTomY(m), getJerryX(m), getJerryY(m));
		}
		else
			cout << "Invalid position of Tom or Jerry" << endl;
	}
	else
		cout << "Unable to open file" << endl;

	system("pause");
	return 0;
}