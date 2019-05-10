/*
*
* by UnitedTimur (c) 2018
*
*/

#pragma once
#include "BoolVector.h"

class plurality : public bv
{
public: 

	plurality();
	plurality(const int &);
	plurality(const char *);
	plurality(const plurality &);
	plurality(const bv &);
	~plurality() {};

	plurality operator=(const plurality &);
	plurality operator+(const plurality &);
	plurality operator+(const char *);
	plurality operator+=(const char *);
	plurality operator+=(const plurality &);
	plurality operator*(const plurality &);
	plurality operator&=(const plurality &);
	plurality operator|(const plurality &);
	plurality operator|=(const plurality &);
	plurality operator-(const plurality &);
	plurality operator-(const char *);
	plurality operator-=(const plurality &);
	plurality operator^(const plurality &);
	plurality operator^=(const plurality &);
	plurality operator~();

	friend ostream & operator<<(ostream &, plurality &);
	friend istream & operator>>(istream &, plurality &);

	void clear();
	void print();

private:
	int power;
};