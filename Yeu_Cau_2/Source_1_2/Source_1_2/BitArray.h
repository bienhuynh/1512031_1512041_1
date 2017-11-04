#pragma once
#define MAX 1000
class BitArray
{
private:
	char data[MAX];
public:
	BitArray();
	void setBit(int n, bool value);
	bool getBit(int n);
};

