/*
*
* by UnitedTimur (c)
*
*/

#pragma once
#include <iostream>

using namespace std;

typedef unsigned char byte;

class bv
{
public:

	bv(int size_vector = 0);
	bv(const char * string, int size_vector = -1);
	bv(const bv & tmp);
	~bv();

	bv & operator=(const bv &);
	friend bv operator&(const bv &, const bv&);
	bv & operator&=(const bv &);
	friend bv operator|(const bv &, const bv &);
	bv & operator|=(const bv &);
	friend bv operator^(const bv &, const bv &);
	bv & operator^=(const bv &);
	bv operator~();
	bv & operator<<=(unsigned int);
	bv & operator>>=(unsigned int);

	friend bv operator<<(const bv &, unsigned int);
	friend bv operator>>(const bv &, unsigned int);

	int operator[](const int);
	
	void setOne(const int);
	void setZero(const int);
	void setOne(int, const int);
	void setZero(int, const int);

	int size() const;
	int weigth() const;

	void print() const;
	void copy(byte*, int);
	void _error() const;

	friend ostream & operator<<(ostream &, bv const&);
	friend istream & operator>>(istream &, bv&);

protected:
	byte* vector;
	int size_vector;
	int memory;
};
