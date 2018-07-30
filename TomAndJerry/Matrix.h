#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// структура клетка
struct Cell
{
	char data; // стойност на клетка 
	bool paint; // дали клетката може да се разлее с боя
};

class Matrix
{ 
	int rows; // редове на матрицата
	int columns; // колони на матрицата
	Cell** darray; // двумерен масив от клетки
	
	// помощна copy функция за copy конструктор и оператор=
	void copy(Matrix const&);

	// създава двумерен масив за посетени клетки
	vector<vector<bool>> createVisited();

	// помощна функция за shortestPaths, намираща всички пътища от дадени начални координати до дадени крайни координати
	void allPaths(int, int, int, int, vector<vector<bool>>&,
		vector<pair<int, int>>, vector<vector<pair<int, int>>>&);

	// помощна функция за printLevel
	bool backPath(vector<string>, int, int, int);
	
	// помощна функция за printPathAsTree, която изкарва по нива дървото от най-кратките пътища
	void printLevel(vector<string>, int, int, int);

public:
	// конструктор по подразбиране за класа Matrix
	Matrix();
	// copy конструктор за класа Matrix
	Matrix(Matrix const&);
	// оператор= за класа Matrix
	Matrix& operator=(Matrix const&);
	// конструктор с редове и колони за класа Matrix
	Matrix(int, int);
	// деструктор за класа Matrix
	~Matrix();
	
	// намира всички най-къси пътища
	// колко боя ще се разлее по всеки от пътищата
	// колко завоя ще се направят по всеки от пътищата
	// команди, които са изпълнени (F(orward), B(ackward), L(eft), R(ight), P(aint))
	void shortestPaths(int, int, int, int);
	
	// функция, изкарваща най-кратките пътища във формата на дърво
	void printPathsAsTree(vector<string>);
	
	// извежда информация за избран път от най-кратките пътища
	void displayChosenPath(vector<string>, vector<int>, vector<int>, int, int, int);

	// достъп до редовете
	int getRows() const;
	// достъп до колоните
	int getColumns() const;
	// достъп до стойността на клетка с дадени координати
	char getCellValue(int, int) const;
	// променя стойността на клетка с дадени координати
	void setCellValue(int, int, char);
	// променя стойността, позволяваща една клетка да бъде боядисана
	void setCellPaint(int, int);
	
	// извежда матрицата
	void printMatrix() const;
};

#endif 