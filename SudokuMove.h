#ifndef SUDOKUMOVE_H
#define SUDOKUMOVE_H

#include <iostream>
#include <string>
#include <chrono>
#include "BitArray.h"

class SudokuMove
{
private:
	BitArray<long long> bitArray;
public:
	SudokuMove();
	SudokuMove(const int&, const size_t&, const size_t&);
	bool operator+=(const SudokuMove&);
	SudokuMove& operator-=(const SudokuMove&);
	friend std::ostream& operator<<(std::ostream&, SudokuMove&);
	size_t GetUnassignedTile();
};

#endif