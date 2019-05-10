/*
*
* by UnitedTimur
*
*/

#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class D_A
{
public:
	D_A();
	D_A(int const&);
	D_A(D_A const&);
	~D_A();

	void operator+(T const&);
	D_A<T> operator+(D_A const&) const;
	D_A<T> operator-(T const&) const;
	void operator-=(T const&);
	void operator+=(T const&);
	void operator=(D_A const&);
	bool operator==(D_A const&) const;

	auto find(char key) -> int;

	T& operator[](T const&);
	auto operator[](int n)->T &;
	T _size() const;
	T *_ptr() const;
	void print();
	void push_back(T const&);
	void pop_back();
	void remove(int const&);

private:
	int size;
	T* ptr;

	friend ostream& operator<< <T> (ostream&, D_A const&);
	friend istream& operator>> <T> (istream&, D_A&);
};

template <typename T>
D_A<T>::D_A()
{
	size = 10;
	ptr = new T[size]{};
}

template <typename T>
D_A<T>::D_A(int const& size)
{
	this->size = size;
	ptr = new T[this->size]{};
	if (typeid(T) == typeid(int))
	{
		for (auto i = 0; i < this->size; i++)
		{
			ptr[i] = rand() % 15 + 1;
		}
	}
	else
	{
		char letter = 'a';
		for (int i = 0; i < size; i++)
		{
			if (!isalpha(letter)) letter = 'a';
			ptr[i] = letter;
			letter += 1;
		}
	}
}

template <typename T>
D_A<T>::D_A(D_A const& tmp)
{
	size = tmp.size;
	ptr = new T[size];

	for (auto i = 0; i < size; i++)
	{
		ptr[i] = tmp.ptr[i];
	}
}

template <typename T>
D_A<T>::~D_A()
{
	delete[] ptr;
}

template <typename T>
void D_A<T>::operator=(D_A const& tmp)
{
	if (size != tmp.size)
	{
		delete[] ptr;
		size = tmp.size;
		ptr = new T[size];
	}

	for (auto i = 0; i < size; i++)
	{
		ptr[i] = tmp.ptr[i];
	}
}

template<typename T>
bool D_A<T>::operator==(D_A const& temp) const
{
	if (size != temp.size)
		return false;

	for (auto i = 0; i < size; i++)
	{
		if (ptr[i] != temp.ptr[i])
			return false;
	}

	return true;
}

template <typename T>
auto D_A<T>::find(char key) -> int
{
	for(auto i = 0; i < size; ++i)
	{
		if (ptr[i].first == key)
		{
			return i;
		}
	}

	return -1;
}

template <typename T>
void D_A<T>::operator+(T const& key)
{
	D_A<T> temp(*this);

	delete[] ptr;
	size += 1;
	ptr = new T[size];

	for (auto i = 0; i < size; i++)
	{
		ptr[i] = temp.ptr[i];
	}

	ptr[size - 1] = key;
}

template <typename T>
D_A<T> D_A<T>::operator+(D_A<T> const& temp) const
{
	D_A<T> tmp(size + temp.size);

	for (auto i = 0; i < size; i++)
	{
		*(tmp.ptr + i) = *(ptr + i);
	}
	for (auto i = 0; i < temp.size; i++)
	{
		*(tmp.ptr + size + i) = *(temp.ptr + i);
	}

	return tmp;
}

template<typename T>
D_A<T> D_A<T>::operator-(T const& index) const
{
	if (index >= 0 && index <= size)
	{
		D_A<T> tmp(*this);

		for (auto i = index; i < tmp.size - 1; i++)
		{
			tmp.ptr[i] = tmp.ptr[i + 1];
		}
		tmp.size--;

		return tmp;
	}
}

template<typename T>
void D_A<T>::operator-=(T const & index)
{
	if (index >= 0 && index <= size)
	{
		for (auto i = index; i < size - 1; ++i)
		{
			ptr[i] = ptr[i + 1];
		}
		size--;

		D_A <T> temp(*this);

		delete[] ptr;
		ptr = new T[size];
		for (auto i = 0; i < size; i++)
		{
			ptr[i] = temp.ptr[i];
		}
	}
}

template<typename T>
void D_A<T>::operator+=(T const & index)
{
	D_A<T> tmp(*this);

	delete[] ptr;
	size += 1;
	ptr = new T[size];

	for (auto i = 0; i < tmp.size; i++)
	{
		ptr[i] = tmp.ptr[i];
	}

	ptr[size - 1] = index;
}

template <typename T>
T &D_A<T>::operator[](T const& index)
{
	if (index >= 0 && index <= size)
	{
		return ptr[index];
	}
}

template <typename T>
auto D_A<T>::operator[](int n) -> T&
{
	return *(ptr + n);
}

template <typename T>
void D_A<T>::print()
{
	for (auto i = 0; i < size; i++)
	{
		std::cout << "[" << ptr[i] << "] ";
	}
}

template<typename T>
void D_A<T>::push_back(T const& key)
{
	D_A<T> tmp(*this);

	delete[] ptr;
	size += 1;
	ptr = new T[size];

	for (auto i = 0; i < size - 1; i++)
	{
		ptr[i] = tmp.ptr[i];
	}

	ptr[size - 1] = key;
}

template<typename T>
void D_A<T>::pop_back()
{
	remove(size);
}

template <typename T>
void D_A<T>::remove(int const& index)
{
	if (index >= 0 && index <= size)
	{
		for (auto i = index; i < size - 1; ++i)
		{
			ptr[i] = ptr[i + 1];
		}
		size--;

		D_A <T> temp(*this);

		delete[] ptr;
		ptr = new T[size];
		for (auto i = 0; i < size; i++)
		{
			ptr[i] = temp.ptr[i];
		}
	}
}

template <typename T>
T D_A<T>::_size() const
{
	return size;
}

template<typename T>
T *D_A<T>::_ptr() const
{
	return ptr;
}

template <typename T>
istream &operator>>(istream& input, D_A<T>& temp)
{
	for (auto i = 0; i < temp.size; i++)
	{
		input >> temp.ptr[i];
	}
	return input;
}

template <typename T>
ostream &operator<<(ostream& output, D_A<T> const& temp)
{
	for (auto i = 0; i < temp.size; i++)
	{
		output << "[" << temp.ptr[i] << "] ";
	}
	output << endl;
	return output;
}