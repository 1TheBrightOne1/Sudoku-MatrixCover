#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstddef>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <stdexcept>

template <class T=size_t>
class BitArray
{
private:
	std::vector<T> bitArray;
	enum { Block_Size = sizeof(T) * CHAR_BIT };
	size_t Capacity() { return bitArray.size() * Block_Size; }
	class Bit
	{
		BitArray& bits;
		size_t pos;
	public:
		Bit(BitArray&, const size_t&);
		operator bool() const;
		typename BitArray::Bit operator=(const bool&);
	};
public:
	explicit BitArray(const size_t&);
	explicit BitArray(const BitArray&) = default;
	BitArray& operator+(const BitArray&) const;
	BitArray& operator+=(const BitArray&);
	BitArray& operator-(const BitArray&) const;
	BitArray& operator-=(const BitArray&);
	bool operator&(const BitArray&) const;
	typename BitArray::Bit operator[](const size_t&);
	std::string ToString();
};

template <class T>
BitArray<T>::BitArray(const size_t& n)
{
	bitArray.resize(n / Block_Size + 1);
}

template <class T>
BitArray<T>& BitArray<T>::operator+(const BitArray& bits) const
{
	BitArray<T>* add;
	BitArray<T> result = bits.bitArray.size() > bitArray.size() ? bits, add = this : *this, add = &bits;
	for (auto ait = result.bitArray.begin(), bit = add->bitArray.begin(); bit != add->bitArray.end(); ++ait, ++bit)
		*ait += *bit;
	return result;
}

template <class T>
BitArray<T>& BitArray<T>::operator+=(const BitArray& bits)
{
	if (bitArray.size() < bits.bitArray.size())
		bitArray.resize(bits.bitArray.size());
	size_t min = std::min(bits.bitArray.size(), bitArray.size());
	for (std::pair<std::vector<T>::iterator, std::vector<T>::const_iterator> iii(bitArray.begin(), bits.bitArray.begin()); iii.first != bitArray.end(); ++iii.first, ++iii.second)
		*(iii.first) += *(iii.second);
	return *this;
}

template <class T>
BitArray<T>& BitArray<T>::operator-(const BitArray& bits) const
{
	BitArray<T>* minus;
	BitArray<T> result = bits.bitArray.size() > bitArray.size() ? bits, add = this : *this, add = &bits;
	for (auto ait = result.bitArray.begin(), bit = add->bitArray.begin(); bit != add->bitArray.end(); ++ait, ++bit)
		*ait -= *bit;
	return result;
}

template <class T>
BitArray<T>& BitArray<T>::operator-=(const BitArray& bits)
{
	if (bitArray.size() < bits.bitArray.size())
		bitArray.resize(bits.bitArray.size());
	size_t min = std::min(bits.bitArray.size(), bitArray.size());
	for (std::pair<std::vector<T>::iterator, std::vector<T>::const_iterator> iii(bitArray.begin(), bits.bitArray.begin()); iii.first != bitArray.end(); ++iii.first, ++iii.second)
		*(iii.first) -= *(iii.second);
	return *this;
}

template <class T>
bool BitArray<T>::operator&(const BitArray& bits) const
{
	size_t min = std::min(bits.bitArray.size(), bitArray.size());
	for (size_t iii = 0; iii < min; ++iii)
	{
		if ((bits.bitArray[iii] & bitArray[iii]) != 0)
			return true;
	}
	return false;
}

template <class T>
typename BitArray<T>::Bit BitArray<T>::operator[](const size_t& pos)
{
	if (pos > Capacity() - 1)
		throw(std::out_of_range("Out of bounds"));
	return Bit(*this, pos);
}

template <class T>
std::string BitArray<T>::ToString()
{
	std::string bits = "";
	for (size_t iii = 0; iii < Capacity(); ++iii)
		(*this)[iii] ? bits += "1" : bits += "0";
	return bits;
}

template <class T>
BitArray<T>::Bit::Bit(BitArray<T>& bits, const size_t& pos) : bits(bits), pos(pos)
{}

template <class T>
BitArray<T>::Bit::operator bool() const
{
	return ((bits.bitArray[pos / Block_Size]) & (T(1) << (pos % Block_Size))) != 0;
}

template <class T>
typename BitArray<T>::Bit BitArray<T>::Bit::operator=(const bool& val)
{
	if (val)
		bits.bitArray[pos / Block_Size] |= T(1) << pos % Block_Size;
	else
		bits.bitArray[pos / Block_Size] &= ~(T(1) << pos % Block_Size);
	return *this;
}

#endif