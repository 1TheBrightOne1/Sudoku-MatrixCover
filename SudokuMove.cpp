#include "SudokuMove.h"

SudokuMove::SudokuMove() : bitArray(324) {}

SudokuMove::SudokuMove(const int& val, const size_t& row, const size_t& col) : bitArray(324)
{
	try 
	{
		bitArray[(row - 1) * 9 + col - 1] = true;
		bitArray[(row - 1) * 9 + val - 1 + 81] = true;
		bitArray[(col - 1) * 9 + val - 1 + 81 * 2] = true;
		bitArray[((row - 1) / 3 * 3 + (col - 1) / 3) * 9 + val - 1 + 81 * 3] = true;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << " at " << val << ", " << row << ", " << col << std::endl;
	}
}

bool SudokuMove::operator+=(const SudokuMove& newMove)
{
	if (bitArray & newMove.bitArray)
	{
		return false;
	}
	bitArray += newMove.bitArray;

	return true;
}

SudokuMove& SudokuMove::operator-=(const SudokuMove& newMove)
{
	bitArray -= newMove.bitArray;
	return *this;
}

std::ostream& operator<<(std::ostream& os, SudokuMove& move)
{
	std::string bits = move.bitArray.ToString();
	os << move.bitArray.ToString() << std::endl;
	return os;
}

size_t SudokuMove::GetUnassignedTile()
{
	for (size_t iii = 0; iii < 81; ++iii)
		if (bitArray[iii] == false)
			return iii;
	return 81;
}