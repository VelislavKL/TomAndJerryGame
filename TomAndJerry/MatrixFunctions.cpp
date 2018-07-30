#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Matrix::copy(Matrix const& copy)
{
	rows = copy.rows;
	columns = copy.columns;

	darray = new Cell*[rows];
	for (int i = 0; i < rows; i++)
		darray[i] = new Cell[columns];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			darray[i][j] = copy.darray[i][j];
	}
}

Matrix::Matrix():darray()
{
	rows = 0;
	columns = 0;
}

Matrix::Matrix(Matrix const& copyconstr)
{
	copy(copyconstr);
}

Matrix& Matrix::operator=(Matrix const& oper)
{
	if (this != &oper)
	{
		copy(oper);
	}

	return *this;
}

Matrix::Matrix(int _rows, int _columns)
{
	rows = _rows;
	columns = _columns;

	darray = new Cell*[rows];
	for (int i = 0; i < rows; i++)
		darray[i] = new Cell[columns];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			darray[i][j].data = '0';
			darray[i][j].paint = false;
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] darray[i];

	delete[] darray;
}

vector<vector<bool>> Matrix::createVisited()
{
	vector<vector<bool>> visited;

	for (int i = 0; i < rows; i++)
	{
		visited.push_back(vector<bool>());
		for (int j = 0; j < columns; j++)
		{
			visited[i].push_back(false);
		}
	}
	return visited;
}

int Matrix::getRows()
const
{
	return rows;
}

int Matrix::getColumns()
const
{
	return columns;
}

char Matrix::getCellValue(int r, int c)
const
{
	return darray[r][c].data;
}

void Matrix::setCellValue(int r, int c, char value)
{
	if (r > rows - 1 || c > columns - 1 || r < 0 || c < 0)
	{
		cout << "Invalid cell!" << endl;
	}

	darray[r][c].data = value;
}

void Matrix::setCellPaint(int r, int c)
{
	if (r > rows - 1 || c > columns - 1 || r < 0 || c < 0)
	{
		cout << "Invalid cell!" << endl;
	}

	darray[r][c].paint = 1;
}

void Matrix::printMatrix()
const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << darray[i][j].data << " ";
		}
		cout << endl;
	}
}

void Matrix::allPaths(int startX, int startY, int endX, int endY, vector<vector<bool>> &visited,
	 vector<pair<int, int>> path, vector<vector<pair<int, int>>> &pathList)
{
	visited[startX][startY] = true;

	path.push_back(make_pair(startX, startY));
	
	// ако се стигне до исканата клетка
	if (startX == endX && startY == endY)
	{
		pathList.push_back(path);
	}
	else
	{
		// проверка за задна клетка
		if (startX + 1 < rows && !visited[startX + 1][startY] &&
			darray[startX + 1][startY].data != '1')
		{
			allPaths(startX + 1, startY, endX, endY, visited, path, pathList);
		}

		// проверка за лява клетка
		if (startY - 1 >= 0 && !visited[startX][startY - 1] &&
			darray[startX][startY - 1].data != '1')
		{
			allPaths(startX, startY - 1, endX, endY, visited, path, pathList);
		}

		// проверка за предна клетка
		if (startX - 1 >= 0 && !visited[startX - 1][startY] &&
			darray[startX - 1][startY].data != '1')
		{
			allPaths(startX - 1, startY, endX, endY, visited, path, pathList);
		}

		// проверка за дясна клетка
		if (startY + 1 < columns && !visited[startX][startY + 1] &&
			darray[startX][startY + 1].data != '1')
		{
			allPaths(startX, startY + 1, endX, endY, visited, path, pathList);
		}
	}
	visited[startX][startY] = false;
}

void Matrix::shortestPaths(int startX, int startY, int endX, int endY)
{
	if (rows * columns <= 1)
		return;
	
	// вектор за посетени клетки
	vector<vector<bool>> visited = createVisited();

	// вектор от точки (път)
	vector<pair<int, int>> path;

	// вектор от пътища
	vector<vector<pair<int, int>>> pathList;

	allPaths(startX, startY, endX, endY, visited, path, pathList);

	// вектор от завои на най-кратките пътища
	vector<int> shortestPathsTurns;
	// вектор от боя, разлята по най-кратките пътища
	vector<int> shortestPathsPaints;
	// вектор от най-кратките пътища
	vector<vector<pair<int, int>>> shortestPaths;
	// вектор от команди, използвани по най-кратките пътища
	vector<string> shortestPathsCommands;

	if (pathList.size() > 0)
	{
		int shortestLen = pathList[0].size();

		// намиране на най-малката дължина на път
		for (int i = 1; i < pathList.size(); i++)
		{
			if (pathList[i].size() < shortestLen)
				shortestLen = pathList[i].size();
		}
		// търсене на пътища с най-малка дължина
		for (int i = 0; i < pathList.size(); i++)
		{
			if (pathList[i].size() == shortestLen)
			{
				string direction;

				shortestPaths.push_back(pathList[i]);
				
				for (int j = 0; j < shortestPaths[shortestPaths.size() - 1].size() - 1; j++)
				{
					if (darray[shortestPaths[shortestPaths.size() - 1][j].first][shortestPaths[shortestPaths.size() - 1][j].second].paint == true)
						direction.push_back('P');

					if (shortestPaths[shortestPaths.size() - 1][j].first < shortestPaths[shortestPaths.size() - 1][j + 1].first)
						direction.push_back('B');

					if (shortestPaths[shortestPaths.size() - 1][j].second < shortestPaths[shortestPaths.size() - 1][j + 1].second)
						direction.push_back('R');

					if (shortestPaths[shortestPaths.size() - 1][j].first > shortestPaths[shortestPaths.size() - 1][j + 1].first)
						direction.push_back('F');
	
					if (shortestPaths[shortestPaths.size() - 1][j].second > shortestPaths[shortestPaths.size() - 1][j + 1].second)
						direction.push_back('L');
				}

				shortestPathsCommands.push_back(direction);

				int turns = 0;
				int paints = 0;
				if (shortestPathsCommands[shortestPaths.size() - 1][0] == 'P' ||
						shortestPathsCommands[shortestPaths.size() - 1][shortestPathsCommands[shortestPaths.size() - 1].size() - 1] == 'P')
					paints++;

				for (int j = 0; j < shortestPathsCommands[shortestPaths.size() - 1].size() - 1; j++)
				{
					if (shortestPathsCommands[shortestPaths.size() - 1][j] == 'P' && j != 0)
					{
						paints++;
						if ((shortestPathsCommands[shortestPaths.size() - 1][j - 1] == 'L' || shortestPathsCommands[shortestPaths.size() - 1][j - 1] == 'R') &&
							(shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'F' || shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'B'))
						{
							turns++;
						}
						if ((shortestPathsCommands[shortestPaths.size() - 1][j - 1] == 'F' || shortestPathsCommands[shortestPaths.size() - 1][j - 1] == 'B') &&
							(shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'L' || shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'R'))
						{
							turns++;
						}
					}
					if ((shortestPathsCommands[shortestPaths.size() - 1][j] == 'L' || shortestPathsCommands[shortestPaths.size() - 1][j] == 'R') &&
							(shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'F' || shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'B'))
					{
						turns++;
					}
					else if ((shortestPathsCommands[shortestPaths.size() - 1][j] == 'F' || shortestPathsCommands[shortestPaths.size() - 1][j] == 'B') &&
						(shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'L' || shortestPathsCommands[shortestPaths.size() - 1][j + 1] == 'R'))
					{
						turns++;
					}
					
				}
				shortestPathsTurns.push_back(turns);
				shortestPathsPaints.push_back(paints);
			}
		}

		printPathsAsTree(shortestPathsCommands);

		cout << endl;
		int choice;
		cout << "Choose path (from 0 to " << shortestPaths.size() - 1 << "): ";
		cin >> choice;

		displayChosenPath(shortestPathsCommands, shortestPathsTurns,
			shortestPathsPaints, shortestPaths.size(), shortestLen, choice);

	}
	else
	{
		cout << "No available path between Tom and Jerry" << endl;
		return;
	}
}

bool Matrix::backPath(vector<string> shortestPathsCommands, int index1, int index2, int level)
{
	if (level < 0)
		return true;

	if (shortestPathsCommands[index1][level] == shortestPathsCommands[index2][level])
		backPath(shortestPathsCommands, index1, index2, level - 1);
	
	else
		return false;
}

void Matrix::printLevel(vector<string> shortestPathsCommands, int maxsize, int reduce, int level)
{
	if (level == maxsize)
		return;

	string levelCommands;

	for (int i = 0; i < shortestPathsCommands.size(); i++)
	{
		levelCommands += shortestPathsCommands[i][level];
	}

	string tempCommands = levelCommands;

	for (int i = 0; i < levelCommands.size() - 1; i++)
	{
		for (int j = i + 1; j < levelCommands.size(); j++)
		{
			if ((levelCommands[i] == levelCommands[j]) && (backPath(shortestPathsCommands, i, j, level - 1)))
			{
				tempCommands.erase(i, 1);
			}
		}
	}

	int offset = maxsize - reduce;

	for (int i = 0; i < offset + 5; i++)
		cout << " ";

	for (int i = 0; i < tempCommands.size(); i++)
	{
		cout << tempCommands[i];

		if (tempCommands.size() % 2 == 0)
		{
			for (int j = 0; j < tempCommands.size(); j++)
				cout << " ";
		}
		else
			for (int j = 0; j < tempCommands.size() - 1; j++)
				cout << " ";
	}

	cout << endl;

	printLevel(shortestPathsCommands, maxsize, reduce + 1, level + 1);
}

void Matrix::printPathsAsTree(vector<string> shortestPathsCommands)
{
	int maxsize = 0;
	
	for (int i = 0; i < shortestPathsCommands.size(); i++)
	{
		if (shortestPathsCommands[i].size() > maxsize)
			maxsize = shortestPathsCommands[i].size();
	}

	int level = 0;
	int reduce = 0;

	for (int i = 0; i < shortestPathsCommands.size(); i++)
	{
		for (int j = 0; j < maxsize; j++)
		{
			shortestPathsCommands[i].push_back(' ');
		}
	}

	printLevel(shortestPathsCommands, maxsize, reduce, level);
}

void Matrix::displayChosenPath(vector<string> shortestPathsCommands, vector<int> pathTurns,
	vector<int> pathPaints, int size, int shortestLen, int choice)
{
	if (choice < size && choice >= 0)
	{
		cout << "Commands: ";
		for (int j = 0; j < shortestPathsCommands[choice].size(); j++)
			cout << shortestPathsCommands[choice][j] << " ";
		cout << endl;

		cout << "Length: " << shortestLen << endl;

		cout << "Painted cells: " << pathPaints[choice] << endl;

		cout << "Made turns: " << pathTurns[choice] << endl;
	}
	else
		cout << "Wrong choice " << endl;
	
	cout << endl;
}
