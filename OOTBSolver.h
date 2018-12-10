#ifndef OOTBSOLVER_H
#define OOTBSOLVER_H

#include <stdio.h> 
#define UNASSIGNED 0 
#define N 9 

class OOTBSolver
{
public:
	/* Takes a partially filled-in grid and attempts to assign values to
	all unassigned locations in such a way to meet the requirements
	for Sudoku solution (non-duplication across rows, columns, and boxes) */
	static bool SolveSudoku(int grid[N][N]);

private:
	// This function finds an entry in grid that is still unassigned 
	static bool FindUnassignedLocation(int grid[N][N], int &row, int &col);

	// Checks whether it will be legal to assign num to the given row, col 
	static bool isSafe(int grid[N][N], int row, int col, int num);

	/* Returns a boolean which indicates whether an assigned entry
	in the specified row matches the given number. */
	static bool UsedInRow(int grid[N][N], int row, int num);

	/* Returns a boolean which indicates whether an assigned entry
	in the specified column matches the given number. */
	static bool UsedInCol(int grid[N][N], int col, int num);

	/* Returns a boolean which indicates whether an assigned entry
	within the specified 3x3 box matches the given number. */
	static bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
};

#endif
