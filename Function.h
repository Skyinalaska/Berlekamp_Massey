#pragma once
#include "Monom.h"

class Function
{
private:
	int size;
	int length;
	Monomial* mon;		
	//int max_mon;		//номер старшего монома в массиве

	void resize(unsigned int new_size);
public:
	Function();
	Function(const Function &old_fun);
	~Function();
	bool is_null();
	int get_length();

	void operator=(const Function &a);
	void operator=(const Monomial &a);
	void operator=(unsigned int a);
	friend Function operator+(Function &a, Function &b);
	friend Function operator+(Function &a, Monomial &b);
	bool f_by_a(bool* a, unsigned int a_size);
	friend bool compare_with_zero(Function &a);
	Function r_shift();

	void print_f();
};

