#include "Function.h"

void Function::resize(unsigned int new_size)
{
	if (size >= new_size)
		return;
	size = new_size;
	length = 0;
	max_mon = 0;
	if (mon)
		delete[] mon;
	mon = new Monomial[new_size];
	return;
}

Function::Function()
{
	length = 0;
	max_mon = 0;
	size = 10;
	mon = new Monomial[10];
}

Function::Function(const Function & old)
{
	size = old.size;
	length = old.length;
	mon = new Monomial[size];
	for (int i = 0; i < length; i++)
	{
		mon[i] = old.mon[i];
	}
}

Function::~Function()
{
	if (mon)
	{
		delete[] mon;
		mon = NULL;
	}
}

//возвращает 1, если равен 0
bool Function::is_null()
{
	if (length == 0)
		return 1;
	for (int i = length - 1; 0 <= i; i--)
	{
		if (compare_with_zero(mon[i]) == 0)
			return 0;
	}
	return 1;
}

void Function::operator=(const Function &a)
{
	if (size < a.size)
	{
		resize(a.size);
	}

	length = a.length;
	max_mon = a.max_mon;
	for (int i = 0; i < a.length; i++)
	{
		mon[i] = a.mon[i];
	}
}

void Function::operator=(const Monomial &a)
{
	length = 1;
	max_mon = 0;
	mon[0] = a;
}

//присваивать только 0!!! 
void Function::operator=(unsigned int a)
{
	if (a == 0)
	{
		for (int i = 0; i < length; i++)
		{
			mon[i] = 0;
		}
		length = 0;
		max_mon = 0;
	}
	else
	{
		std::cout << "Error, can't = " << a << std::endl;
	}
}

Function operator+(Function &a, Function &b)
{
	Function result;
	if (result.size < (a.length + b.length))
	{
		result.resize(a.length + b.length);
	}

	//проверку на пустые функции делаем? 
	result.length = a.length + b.length;
	int i = 0;
	for (; i < a.length; i++)
	{
		result.mon[i] = a.mon[i];
	}
	for (; i < result.length; i++)
	{
		result.mon[i + a.length] = b.mon[i];
	}

	if (a.mon[a.max_mon] < b.mon[b.max_mon])
	{
		result.max_mon = b.max_mon + a.length;
	}
	else
	{
		result.max_mon = a.max_mon;
	}

	return result;
}

Function operator+(Function &a, Monomial &b)
{
	Function result;
	if (result.size < (a.length + 1))
	{
		result.resize(a.length + 1);
	}
	result = a;
	result.mon[result.length] = b;
	if (a.mon[a.max_mon] < b)
	{
		result.max_mon = result.length;
	}
	result.length++;
	return result;
}


bool Function::f_by_a(bool* a, unsigned int a_size)
{
	bool res = 0;
	if (length == 0)
	{
		std::cout << "Error, f = 0" << std::endl;
		return 0;
	}

	for (int i = 0; i < length; i++)
	{
		res = res ^ mon[i].Tm_by_a(a, a_size);
	}

	return res;
}

//возвращает 1, если а равен 0;
bool compare_with_zero(Function &a)
{
	if (a.length == 0)
		return 1;
	for (int i = a.length - 1; 0 <= i; i--)
	{
		if (compare_with_zero(a.mon[i]) == 0)
			return 0;
	}
	return 1;
}

Function Function::r_shift()
{
	Function res;
	if (res.size < length)
	{
		res.resize(length);
	}
	res.length = length;

	for (int i = 0; i < length; i++)
	{
		res.mon[i] = mon[i].r_shift();
	}
	return res;
}