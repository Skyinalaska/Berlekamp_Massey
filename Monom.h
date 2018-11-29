#pragma once
#include <iostream>


class Monomial
{
private:
	bool* arr;
	int size;					//Общий размер выделенной 
	int length;					//Размер (длина) значимой части
	
	void resize(unsigned int new_size);
	friend bool compare_with_zero(Monomial& a);
public:
	Monomial();
	Monomial(const Monomial& old_mon);
	~Monomial();
	void change_to_monom_i(unsigned int);
	Monomial l_shift();
	Monomial r_shift();
	bool can_lshift();
	bool is_null();

	//Monomial& operator=(Monomial &a);
	void operator=(const Monomial &a);
	void operator=(unsigned int a);

	Monomial& operator++();
	//Monomial operator++(int);
	bool Tm_by_a(bool* a, unsigned int a_size);

	friend int compare(const Monomial& a, const Monomial& b);

	friend bool operator>(const Monomial& a, const Monomial& b);
	friend bool operator<(const Monomial& a, const Monomial& b);
	friend bool operator>=(const Monomial& a, const Monomial& b);
	friend bool operator<=(const Monomial& a, const Monomial& b);
	friend bool operator==(const Monomial& a, const Monomial& b);
	friend void print(const Monomial& a);
};

