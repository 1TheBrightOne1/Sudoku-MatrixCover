#include <iostream>
#include <string>
#include <stdexcept>
#include <list>
#include <vector>
#include <chrono>

#include "SudokuMove.h"
#include "OOTBSolver.h"

struct solution
{
	int row, col, val;
	solution(int row, int col, int val) : row(row), col(col), val(val) {}
};

bool SolveSudoku(SudokuMove& board, int grid[9][9])
{
	size_t index = board.GetUnassignedTile();
	if (index == 81)
		return true;

	for (int iii = 1; iii <= 9; ++iii)
	{
		SudokuMove newMove(iii, index / 9 + 1, index % 9 + 1);
		if (board += newMove)
		{
			if (SolveSudoku(board, grid))
			{
				return true;
			}
			else
			{
				board -= newMove;
			}
		}
	}

	return false;
}

void PrintBoard(int grid[9][9])
{
	for (int iii = 0; iii < 9; ++iii)
	{
		for (int jjj = 0; jjj < 9; ++jjj)
		{
			std::cout << " " << grid[iii][jjj] << " ";
			if (jjj == 2 || jjj == 5)
				std::cout << "|";
		}
		std::cout << std::endl;
		if (iii == 2 || iii == 5)
			std::cout << "-----------------------------" << std::endl;	
	}
}

int main()
{
	int grid[9][9] =
	{ { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
	{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
	{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
	{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
	{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
	{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
	{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
	{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
	{ 0, 0, 0, 0, 8, 0, 0, 7, 9 } };

	int grid2[9][9] = 
	{ { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
	{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
	{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
	{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
	{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
	{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
	{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
	{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
	{ 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
	
	std::list<std::pair<size_t, size_t>> openTiles;
	
	std::vector<solution> solvedBoard;
	SudokuMove state;

	for (int row = 0; row < 9; ++row)
		for (int col = 0; col < 9; ++col)
			if (grid[row][col] == 0)
				openTiles.push_back(std::pair<int, int>(row + 1, col + 1));
			else
			{
				if (!(state += SudokuMove(grid[row][col], row + 1, col + 1)))
				{
					std::cout << "Invalid Board!" << row + 1 << ", " << col + 1 << ", " << grid[row][col] << std::endl;
				}
			}
	auto start = std::chrono::high_resolution_clock::now();
	if (SolveSudoku(state, grid))
	{
		PrintBoard(grid);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	std::cout << "\n" << std::chrono::duration<double>(stop - start).count() << std::endl;

	start = std::chrono::high_resolution_clock::now();

	if (OOTBSolver::SolveSudoku(grid2))
		PrintBoard(grid2);

	stop = std::chrono::high_resolution_clock::now();

	std::cout << "\n" << std::chrono::duration<double>(stop - start).count() << std::endl;

	std::cin.get();
	return 0;
}