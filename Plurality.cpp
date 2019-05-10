/*
*
* by UnitedTimur (c) 2018
*
*/

#include "Plurality.h"
#define encoding_length 256

plurality::plurality() : bv(encoding_length)
{
	power = 0;
}

plurality::plurality(const int & size_vector) : bv(size_vector)
{
	power = 0;
}

plurality::plurality(const char * string) : bv(encoding_length)
{
	for (int i = 0; string[i]; i++)
	{
		setOne((int)string[i]);
	}

	power = weigth();
}

plurality::plurality(const plurality & tmp) : bv(tmp)
{
	power = tmp.power;
}

plurality::plurality(const bv & tmp) : bv(tmp) {}

plurality plurality::operator=(const plurality & tmp)
{
	if (this != &tmp)
	{
		bv::operator=(tmp);
		power = tmp.power;
		return *this;
	}
	else
	{
		cout << "//Fatal error. Watch 'operator=.'" << endl;
		system("pause");
		exit(1);
	}
}

plurality plurality::operator+(const plurality & tmp)
{
	if (this != &tmp)
	{

		plurality temp(*this);

		temp |= tmp;

		temp.power = temp.weigth();

		return temp;
	}

	return *this;
}

plurality plurality::operator+(const char * string)
{
	plurality temp(*this);

	for (int i = 0; string[i]; i++)
	{
		temp.setOne(string[i]);
	}

	temp.power = weigth();

	return temp;
}

plurality plurality::operator+=(const char * string)
{
	for (int i = 0; string[i]; i++)
	{
		setOne(string[i]);
	}

	power = weigth();

	return *this;
}

plurality plurality::operator+=(const plurality & tmp)
{
	*this |= tmp;

	power = weigth();

	return *this;
}

plurality plurality::operator*(const plurality & tmp)
{
	if (this != &tmp)
	{
		plurality temp(*this);

		temp &= tmp;

		temp.power = temp.weigth();

		return temp;
	}

	return *this;
}

plurality plurality::operator&=(const plurality & tmp)
{
	return bv::operator&=(tmp);
}

plurality plurality::operator|(const plurality & tmp)
{
	if (this != &tmp)
	{
		plurality temp(*this);

		temp |= tmp;

		temp.power = temp.weigth();

		return temp;
	}

	return *this;
}

plurality plurality::operator|=(const plurality & tmp)
{
	return bv::operator|=(tmp);
}

plurality plurality::operator-(const plurality & tmp)
{
	if (this != &tmp)
	{
		plurality temp(*this);
		
		temp &= ~(temp & tmp);

		temp.power = temp.weigth();

		return temp;
	}

	return *this;
}

plurality plurality::operator-(const char * string)
{
	plurality temp(*this);

	for (int i = 0; i < size_vector; i++)
	{
		temp.setZero(string[i]);
	}

	temp.power = temp.weigth();

	return temp;
}

plurality plurality::operator-=(const plurality & tmp)
{
	*this &= ~(*this & tmp);

	power = weigth();

	return *this;
}

plurality plurality::operator^(const plurality & tmp)
{
	if (this != &tmp)
	{
		plurality temp(*this);

		temp ^= tmp;

		temp.power = temp.weigth();

		return temp;
	}

	return *this;
}

plurality plurality::operator^=(const plurality & tmp) 
{
	return bv::operator^=(tmp);
}

plurality plurality::operator~()
{
	return bv::operator~();
}

void plurality::clear()
{
	setZero(0, encoding_length);
	power = 0;
}

void plurality::print()
{
	cout << "Power is equal " << power << "." << endl;

	for (int i = 0; i < size_vector; i++)
	{
		if (operator[](i) == 1)
		{
			cout << (char)i;
		}
	}

	if (power) cout << endl;
}

ostream & operator<<(ostream & os, plurality & tmp)
{
	os << "Power is equal " << tmp.power << "." << endl;

	for (int i = 0; i < tmp.size_vector; i++)
	{
		if (tmp[i] == 1)
		{
			cout << (char)i;
		}
	}

	return os;
}

istream & operator>>(istream & is, plurality & tmp)
{
	char * string = new char [encoding_length] {};

	cout << "Enter your string, please: ";

	is.getline(string, encoding_length);

	tmp.setZero(0, encoding_length);

	for (int i = 0; string[i]; i++)
	{
		tmp.setOne((int)string[i]);
	}

	return is;
}