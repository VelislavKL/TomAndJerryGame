#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ��������� ������
struct Cell
{
	char data; // �������� �� ������ 
	bool paint; // ���� �������� ���� �� �� ������ � ���
};

class Matrix
{ 
	int rows; // ������ �� ���������
	int columns; // ������ �� ���������
	Cell** darray; // �������� ����� �� ������
	
	// ������� copy ������� �� copy ����������� � ��������=
	void copy(Matrix const&);

	// ������� �������� ����� �� �������� ������
	vector<vector<bool>> createVisited();

	// ������� ������� �� shortestPaths, �������� ������ ������ �� ������ ������� ���������� �� ������ ������ ����������
	void allPaths(int, int, int, int, vector<vector<bool>>&,
		vector<pair<int, int>>, vector<vector<pair<int, int>>>&);

	// ������� ������� �� printLevel
	bool backPath(vector<string>, int, int, int);
	
	// ������� ������� �� printPathAsTree, ����� ������� �� ���� ������� �� ���-�������� ������
	void printLevel(vector<string>, int, int, int);

public:
	// ����������� �� ������������ �� ����� Matrix
	Matrix();
	// copy ����������� �� ����� Matrix
	Matrix(Matrix const&);
	// ��������= �� ����� Matrix
	Matrix& operator=(Matrix const&);
	// ����������� � ������ � ������ �� ����� Matrix
	Matrix(int, int);
	// ���������� �� ����� Matrix
	~Matrix();
	
	// ������ ������ ���-���� ������
	// ����� ��� �� �� ������ �� ����� �� ��������
	// ����� ����� �� �� �������� �� ����� �� ��������
	// �������, ����� �� ��������� (F(orward), B(ackward), L(eft), R(ight), P(aint))
	void shortestPaths(int, int, int, int);
	
	// �������, ��������� ���-�������� ������ ��� ������� �� �����
	void printPathsAsTree(vector<string>);
	
	// ������� ���������� �� ������ ��� �� ���-�������� ������
	void displayChosenPath(vector<string>, vector<int>, vector<int>, int, int, int);

	// ������ �� ��������
	int getRows() const;
	// ������ �� ��������
	int getColumns() const;
	// ������ �� ���������� �� ������ � ������ ����������
	char getCellValue(int, int) const;
	// ������� ���������� �� ������ � ������ ����������
	void setCellValue(int, int, char);
	// ������� ����������, ����������� ���� ������ �� ���� ���������
	void setCellPaint(int, int);
	
	// ������� ���������
	void printMatrix() const;
};

#endif 