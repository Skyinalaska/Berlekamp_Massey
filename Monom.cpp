//#ifndef MONOM_H
//#define MONOM_H
#pragma once 
#include "Monom.h"

void Monomial::resize(unsigned int new_size)
{
	if (size >= new_size)
		return;
	size = new_size;
	length = 0;
	if (arr)
		delete[] arr;
	arr = new bool[new_size];
	for (int i = 0; i < new_size; i++)
	{
		arr[i] = 0;
	}
	return;
}

//Function operator+(const Monomial& a, const Monomial& b)
//{
//	Function res;
//	res.length;
//	return res;
//}

Monomial::Monomial()
{
	size = 10;
	length = 0;
	arr = new bool[10];
	for (int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
}

Monomial::Monomial(const Monomial & old)
{
	size = old.size;
	length = old.length;
	arr = new bool[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = old.arr[i];
	}
}

Monomial::~Monomial()
{
	if (arr)
	{
		delete[] arr;
		arr = NULL;
	}
}

void Monomial::change_to_monom_i(unsigned int n)
{
	if (size <= n)
	{
		resize(n + 1);
	}
	for (int i = 0; i < n; i++)
		arr[i] = 0;
	length = n + 1;
	arr[n] = 1;
}

Monomial Monomial::l_shift()
{
	//return моном m с периодом -1 
	Monomial result;
	if (arr[0] == 1)
	{
		std::cout << "Warning! Can't l_shift" << std::endl;
		return result;
	}

	if (result.size < length)
	{
		result.resize(length);
	}

	result.length = length;
	for (int i = 0; i < length - 1; i++)
	{
		result.arr[i] = arr[i + 1];
	}
	result.length--;
	return result;
}

Monomial Monomial::r_shift()
{
	Monomial result;
	if (result.size < (length + 1) )
	{
		result.resize(length + 1);
	}

	result.length = length;
	result.arr[0] = 0;
	for (int i = 0; i < length; i++)
	{
		result.arr[i + 1] = arr[i];
	}
	result.length++;
	return result;
}

bool Monomial::can_lshift()				//возвращает 1, если может l_shift
{
	if (length <= 1)
		return false;
	if (arr[0] == 1)
		return false;
	return true;
}

bool Monomial::is_null()
{
	for (int i = length - 1; 0 <= i; i--)
	{
		if (arr[i] != 0)
			return 0;
	}
	return 1;
}

void Monomial::operator=(const Monomial &a)
{
	if (size < a.size)
	{
		resize(a.size);
	}

	length = a.length;
	for (int i = 0; i < a.length; i++)
	{
		arr[i] = a.arr[i];
	}
}

//Monomial& Monomial::operator=(Monomial &a)
//{
//	if (this == &a)
//		return *this;
//	if (size < a.size)
//	{
//		resize(a.size);
//	}
//
//	length = a.length;
//	for (int i = 0; i < a.length; i++)
//	{
//		arr[i] = a.arr[i];
//	}
//	return *this;
//}

void Monomial::operator=(unsigned int a)
{
	if (a == 0)
	{
		resize(10);
		length = 0;
	}
	else
	{
		std::cout << "Error, can't = " << a << std::endl;
	}
}

Monomial& Monomial::operator++()
{
	if (length == 0)
	{
		length++;
		arr[0] = 1;
		return *this;
	}
	if (length == 1)
	{
		length++;
		arr[1] = 1;
		arr[0] = 0;
		return *this;
	}
	if ((arr[length - 1] == 1) && (arr[length - 2] == 1))
	{
		length++;
		if (length > size)
		{
			this->resize(length);
		}
		arr[length - 3] = 0;
		arr[length - 2] = 0;
		arr[length - 1] = 1;
		return *this;
	}
	if ((arr[length - 1] == 1) && (arr[length - 2] == 0))
	{
		for (int i = 0; i < length - 2; i++)
		{
			if (arr[i] == 1)
			{
				arr[i] = 0;
				arr[i + 1] = 1;
				return *this;
			}
		}
		arr[0] = 1;
		return *this;
	}
	return *this;
}

//Monomial Monomial::operator++(int)
//{
//	Monomial temp();
//}

bool Monomial::Tm_by_a(bool* a, unsigned int a_size)
{
	if (compare_with_zero(*this) == 1)
	{
		std::cout << "Error, Tm = 0" << std::endl;
		return 0;
	}
	if (length > a_size)
	{
		std::cout << "Error, mon's size > sequence's size" << std::endl;
		return 0;
	}
	bool result = 1;
	for (int i = 0; i < length; i++)
	{
		if (arr[i] == 1)
		{
			result = result && a[i];
		}
	}
	return result;
}

void print(const Monomial& a)
{
	for (int i = a.length - 1; i >= 0; i--)
		if(a.arr[i] == 1)
			std::cout << i;
	//std::cout << std::endl;
}

/*----------------------------------------------*/

int compare(const Monomial& a, const Monomial& b)
{
	//возвращает 1, если а > b; возвращает -1, если а < b;
	//возвращает 0, если а == b
	if (a.length > b.length)
		return 1;
	if (a.length < b.length)
		return -1;
	for (int i = a.length - 1; 0 <= i; i--)
	{
		if (a.arr[i] > b.arr[i])
			return 1;
		if (a.arr[i] < b.arr[i])
			return -1;
	}
	return 0;
}

bool compare_with_zero(Monomial& a)
{
	for (int i = a.length - 1; 0 <= i; i--)
	{
		if (a.arr[i] != 0)
			return false;
	}
	return true;
}


bool operator>(const Monomial& a, const Monomial& b)
{
	if (compare(a, b) == 1)
		return true;
	return false;
}

bool operator<(const Monomial& a, const Monomial& b)
{
	if (compare(a, b) == -1)
		return true;
	return false;
}

bool operator>=(const Monomial& a, const Monomial& b)
{
	if (compare(a, b) == -1)
		return false;
	return true;
}

bool operator<=(const Monomial& a, const Monomial& b)
{
	if (compare(a, b) == 1)
		return false;
	return true;
}

bool operator==(const Monomial& a, const Monomial& b)
{
	if (compare(a, b) == 0)
		return true;
	return false;
}