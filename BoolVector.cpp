/*
*
* by UnitedTimur (c) 2018
*
*/

#include "BoolVector.h"

using namespace std;

bv::bv(int size_vector)
{
	if (size_vector)
	{
		this->size_vector = size_vector;
		memory = (this->size_vector - 1) / 8 + 1;
		vector = new byte[memory]();
	}
	else
	{
		vector = nullptr;
	}
}

bv::bv(const char * string, int size_vector)
{
	memory = 0;
	int index;

	if (size_vector == -1)
	{
		this->size_vector = strlen(string);
		index = this->size_vector - 1;
	}
	else
	{
		this->size_vector = size_vector;
		index = strlen(string) - 1;
	}

	if (this->size_vector)
	{
		memory = (this->size_vector - 1) / 8 + 1;
		vector = new byte[memory]();

		int indmas = memory - 1;
		byte mask = 1;

		for (int count = this->size_vector; count > 0; count--, index--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				indmas--;
			}

			if (string[index] == '1')
			{
				vector[indmas] |= mask;
			}
		}
	}
}

bv::bv(const bv & tmp)
{
	if (this != &tmp)
	{
		memory = tmp.memory;
		size_vector = tmp.size_vector;

		if (memory)
		{
			vector = new byte[memory]();

			for (int i = 0; i < memory; i++)
			{
				vector[i] = tmp.vector[i];
			}
		}
	}
	else
	{
		vector = nullptr;
	}
}

bv::~bv()
{
	delete[] vector;
}

bv & bv::operator=(const bv & tmp)
{
	if (this != &tmp)
	{
		delete[] vector;
		size_vector = tmp.size_vector;
		memory = (size_vector - 1) / 8 + 1;
		vector = new byte[memory]();

		for (int i = 0; i < memory; i++)
		{
			vector[i] = tmp.vector[i];
		}
	}

	return *this;
}

bv & bv::operator&=(const bv & tmp)
{
	for (int i = memory - 1, j = tmp.memory - 1; i >= 0 && j >= 0; i--, j--)
	{
		vector[i] &= tmp.vector[j];
	}
	for (int i = memory - tmp.memory - 1; i >= 0; i--)
	{
		vector[i] = 0;
	}

	return *this;
}

bv & bv::operator|=(const bv & tmp)
{
	for (int i = memory - 1, j = tmp.memory - 1; i >= 0 && j >= 0; i--, j--)
	{
		vector[i] |= tmp.vector[j];
	}

	return *this;
}

bv & bv::operator^=(const bv & tmp)
{
	for (int i = memory - 1, j = tmp.memory - 1; i >= 0 && j >= 0; i--, j--)
	{
		vector[i] ^= tmp.vector[j];
	}

	return *this;
}

bv bv::operator~()
{
	try
	{
		if (memory == 0)
		{
			throw "//Error. The size of vector is 0.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	bv temp(*this);

	for (int i = 0; i < temp.memory; i++)
	{
		temp.vector[i] = ~vector[i];
	}

	return temp;
}

bv & bv::operator<<=(unsigned int key)
{
	int count = 0;
	for (int i = 0; i < key; i++)
	{
		for (int j = memory - 1; j >= 0; j--)
		{
			bool one = vector[j] & (1 << 7) ? true : false;

			vector[j] <<= 1;

			if (count)
			{
				vector[j] |= 1;
				count--;
			}
			if (one)
			{
				count++;
			}
		}
	}

	return *this;
}

bv & bv::operator>>=(unsigned int key)
{
	int count = 0; 

	for (int i = 0; i < key; i++)
	{
		for (int j = 0; j < memory; j++)
		{
			bool one = vector[j] & 1 ? true : false;

			vector[j] >>= 1;
			
			if (count)
			{
				vector[j] |= 1 << 7;
				count--;
			}

			if (one)
			{
				count++;
			}
		}
	}

	return *this;
}

int bv::operator[](const int key)
{
	if (key >= 0 && key <= size_vector)
	{
		int i = memory - 1 - key / 8;
		int bit = key % 8;

		byte mask = 1 << bit;

		if (vector[i] & mask)
		{
			return 1;
		}

		return 0;
	}

	return 0;
}

void bv::setOne(const int key)
{
	if (key >= 0 && key <= size_vector)
	{
		int i = memory - 1 - key / 8;
		int bit = key % 8;

		byte mask = 1 << bit;

		vector[i] |= mask;
	}
}

void bv::setZero(const int key)
{
	if (key >= 0 && key <= size_vector)
	{
		int i = memory - 1 - key / 8;
		int bit = key % 8;

		byte mask = 1 << bit;

		if (operator[](key))
		{
			mask = ~mask;
			vector[i] &= mask;
		}
	}
}

void bv::setOne(int key, const int number)
{
	if (key >= 0 && key <= size_vector)
	{
		for (auto i = key; i < key + number; i++)
		{
			setOne(i);
		}
	}
}

void bv::setZero(int key, const int number)
{
	if (key >= 0 && key <= size_vector)
	{
		for (auto i = key; i < key + number; i++)
		{
			setZero(i);
		}
	}
}

int bv::size() const
{
	return size_vector;
}

int bv::weigth() const
{
	byte mask;

	auto count = 0;

	for (auto index_string = 0; index_string < memory; index_string++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}

			if (vector[index_string] & mask)
			{
				count++;
			}
		}
	}

	return count;
}

void bv::print() const
{
	byte mask = 1 << size_vector - memory * 8 + 7;

	for (int i = 0; i < memory; i++)
	{
		while (mask)
		{
			cout << (vector[i] & mask ? 1 : 0);
			mask >>= 1;
		}

		mask = 1 << 7;
	}
}

void bv::copy(byte * tmp, int nmas)
{
	for (auto i = 0; i < nmas; i++)
	{
		vector[i] = tmp[i];
	}
}

void bv::_error() const
{
	system("pause");
	exit(0);
}

bv operator&(const bv & tmp1, const bv & tmp2)
{
	bv temp(tmp1.size_vector < tmp2.size_vector ? tmp2.size_vector : tmp1.size_vector);
	for (int i = tmp1.memory - 1, j = tmp2.memory - 1, ind = temp.memory - 1; i >= 0 && j >= 0; ind--, i--, j--)
	{
		temp.vector[ind] = tmp1.vector[i] & tmp2.vector[j];
	}

	return temp;
}

bv operator|(const bv & tmp1, const bv & tmp2)
{
	bv temp(tmp1.size_vector < tmp2.size_vector ? tmp2 : tmp1);
	for (int i = tmp1.memory - 1, j = tmp2.memory - 1, ind = temp.memory - 1; i >= 0 && j >= 0; ind--, i--, j--)
	{
		temp.vector[ind] = tmp1.vector[i] | tmp2.vector[j];
	}

	return temp;
}

bv operator^(const bv & tmp1, const bv & tmp2)
{
	bv temp(tmp1.size_vector < tmp2.size_vector ? tmp1 : tmp2);
	for (int i = tmp1.memory - 1, j = tmp2.memory - 1, ind = temp.memory - 1; i >= 0 && j >= 0; ind--, i--, j--)
	{
		temp.vector[ind] = tmp1.vector[i] ^ tmp2.vector[j];
	}

	return temp;
}

bv operator<<(const bv & tmp, unsigned int key)
{
	bv temp(tmp);

	temp <<= key;

	return temp;
}

bv operator>>(const bv & tmp, unsigned int key)
{
	bv temp(tmp);

	temp >>= key;

	return temp;
}

ostream & operator<<(ostream & os, bv const & tmp)
{
	byte mask;

	for (auto index_string = 0; index_string < tmp.memory; index_string++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}

			if (tmp.vector[index_string] & mask)
			{
				os << '1';
			}
			else
			{
				os << '0';
			}
		}
	}

	return os;
}

istream & operator>>(istream & is, bv & tmp)
{
	char * s;

	int size;

	cout << "Enter the length of your vector, please: ";

	cin >> size;

	s = new char[size + 1] {};

	cout << "Enter the vector, please: ";

	cin >> s;

	try
	{
		if (strlen(s) != size) throw "//The length of vector is more than the entered length.";

		for (auto i = 0; i < strlen(s); i++)
		{
			if (!isdigit(s[i]) || s[i] != '0' && s[i] != '1')
			{
				throw "//Not all symbols are zero or one.";
			}
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		tmp._error();
	}

	tmp.size_vector = strlen(s);
	tmp.memory = (tmp.size_vector - 1) / 8 + 1;
	tmp.vector = new byte[tmp.memory]{};

	byte mask = 1;

	auto index_string = tmp.memory - 1;

	for (auto i = tmp.size_vector - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			index_string--;
		}

		if (s[i] == '1')
		{
			tmp.vector[index_string] |= mask;
		}
	}

	return is;
}