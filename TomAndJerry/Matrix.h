#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Cell
{
	char data;
	bool paint;
};

class Matrix
{ 
	int rows; 
	int columns; 
	Cell** darray; 
	
	void copy(Matrix const&);

	vector<vector<bool>> createVisited();
	
	void allPaths(int, int, int, int, vector<vector<bool>>&,
		vector<pair<int, int>>, vector<vector<pair<int, int>>>&);
	bool backPath(vector<string>, int, int, int);
	
	void printLevel(vector<string>, int, int, int);

public:
	Matrix();
	Matrix(Matrix const&);
	Matrix& operator=(Matrix const&);
	Matrix(int, int);
	~Matrix();
	
	void shortestPaths(int, int, int, int);
	void printPathsAsTree(vector<string>);
	void displayChosenPath(vector<string>, vector<int>, vector<int>, int, int, int);
	int getRows() const;
	int getColumns() const;
	char getCellValue(int, int) const;
	void setCellValue(int, int, char);
	void setCellPaint(int, int);
	void printMatrix() const;
};

#endif 
