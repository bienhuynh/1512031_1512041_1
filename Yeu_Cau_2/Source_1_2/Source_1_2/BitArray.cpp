#include "BitArray.h"




BitArray::BitArray()
{
	for (size_t i = 0; i < MAX; i++)
	{
		data[i] = 0;
	}
}

void BitArray::setBit(int n, bool value)
{
	if (n >= MAX) return;
	int vt = n / 8;
	int bit = n % 8;
	char v1 = 1 << (bit);
	char v2 = 0b11111111 - (1 << (bit));
	if (value) data[vt] = data[vt] | v1;
	else data[vt] = data[vt] & v2;
}

bool BitArray::getBit(int n)
{
	if (n >= MAX) return false;
	int vt = n / 8;
	int bit = n % 8;
	char v1 = 1 << (bit);
	return (data[vt] & v1) > 0;
}
