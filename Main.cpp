#include <iostream>
#include <map>
#include <algorithm>

#include "Monom.h"
#include "Function.h"

bool randomBool() {
	return rand() > (RAND_MAX / 2);
}

//Function Berlekamp_Massey(bool* a, unsigned int N)
void Berlekamp_Massey(bool* a, unsigned int N)
{
	bool b;
	Monomial mon_i, mon_i_1, m;				//x[i],  x[i+1],  m
	Monomial m_prev, m_l_shift;				//m',    m^(-1)
	Monomial T0_m, T0_m_prev;				//T0(m), T0(m')

	Function s[2], s1_less;					// s0(m),  s1(m),  s1(<=m);
	Function s_tmp, s1_less_prev;			// s/s(m),  s1(<=m')

	int t1_less = 0, t[2] = { 0, 0 };
	int t1_less_prev = 0, t_res;			//t1(<=m');

	//m^(-1) -> s0(m^(-1)), t0(m^(-1));
	std::map <Monomial, std::pair <Function, int>> s0_lshift;
	std::pair <Function, int> tmp_pair;

	for (int i = 0; i < (N - 1); i++)
	{
		mon_i.change_to_monom_i(i);
		mon_i_1.change_to_monom_i(i + 1);
		for (m = mon_i; m < mon_i_1; ++m)	//что если i=0?
		{
			if (T0_m_prev.is_null() && (m.Tm_by_a(a, N) == 1)) {
				T0_m = m;
			}
			else {
				T0_m = T0_m_prev;
			}

			//проверка, что m^(-1) = 0 и s0(m^(-1)) = 0
			m_l_shift = m.l_shift();
			s_tmp = s0_lshift[m_l_shift].first;

			if ((m.can_lshift() == 1) && (s_tmp.is_null() == 0))	//s!=0
			{
				//0 
				s_tmp = s_tmp.r_shift();
				b = s_tmp.r_shift().f_by_a(a, N);			//b = s^(2)(a)

				s[b] = s_tmp;
				t[b] = s0_lshift[m_l_shift].second + 1;
				t[!b] = std::min(t[0], t1_less_prev);
				if (s1_less_prev.is_null() == 1)
					s[!b] = 0;
				else
					s[!b] = s[b] + s1_less_prev;

				if (t[1] > t1_less_prev)
				{
					s1_less = s[1];
					t1_less = t[1];
				}
				else
				{
					s1_less = s1_less_prev;
					t1_less = t1_less_prev;
				}

				s0_lshift.erase(m_l_shift);
			}
			else					//иначе эта ветка s = 0;
			{
				t[0] = 0;
				t[1] = 0;
				t1_less = t1_less_prev;
				if (m.Tm_by_a(a, N) == 0)				//Tm(a) = 0
				{
					s_tmp = m;
				}
				else
				{
					if (T0_m_prev.is_null() == 1)		//To(m') = 0
					{
						s_tmp = 0;
					}
					else										//To(m') != 0
					{
						s_tmp = m;
						s_tmp = s_tmp + T0_m_prev;
					}
				}

				if (s_tmp.is_null() == 1)						//if s(m) = 0
				{
					s[0] = 0;
					s[1] = 0;
				}
				else											//s(m) != 0
				{
					b = s_tmp.r_shift().f_by_a(a, N);
					s[b] = s_tmp;
					if (s1_less_prev.is_null() == 1)		//s1(<=m') = 0 
					{
						s[!b] = 0;
					}
					else
					{
						s[!b] = s[b] + s1_less_prev;
					}
				}

				if (s1_less_prev.is_null() == 1)		//s1(<=m') = 0
				{
					s1_less = s[1];
				}
				else
				{
					s1_less = s1_less_prev;
				}
			}

			tmp_pair = std::make_pair(s[0], t[0]);
			s0_lshift.insert(std::pair<Monomial, std::pair<Function, int> >(m, tmp_pair));
			T0_m_prev = T0_m;
			s1_less_prev = s1_less;
			t1_less_prev = t1_less;
			//print(m); std::cout << " -> s = "; s.print_f();
			//std::cout << " s0(m) = "; s0.print_f();
			//std::cout << " s1(m) = "; s1.print_f();
			//std::cout << " s1(<=m) = "; s1_less.print_f();
			//std::cout << std::endl;
		}
	}

	if ((T0_m_prev.is_null() == 0) || (a[N] == 0))
	{
		t_res = std::max(t[0], t[1]);
		
		std::cout << "complexity = " << N - t_res << std::endl;
		std::cout << "min func = ";
		if ((t[0] >= t[1]) && (s[0].is_null() == 1))
			s[0].print_f();
		else
			s[1].print_f();
	}
	else
		std::cout << "min func is exist" << std::endl;
}




int main()
{
	unsigned int N; //sequence size 
	/*std::cin >> N;
	bool* a = new bool[N];
	std::cout << "Input bool array a:" << std::endl;
	for (int i = 0; i < N; i++)
		std::cin >> a[i];
*/
	N = 5;
	bool* a = new bool[N];
	//a[0] = 0; a[1] = 1; a[2] = 0; a[3] = 1; a[4] = 1;
	for (int i = 0; i < N; i++)
	{
		a[i] = randomBool();
		std::cout << a[i];
	}
	std::cout << std::endl;
	Berlekamp_Massey(a, N);
	
	

	//++m;
	//++m;
	//Monomial b;
	//++b; print(b);
	//++b; print(b);
	//++b; print(b);
	//++b; print(b);
	//++m; ++m; ++m; //m = 5; b = 4;
	//print(m);
	//m = b.r_shift();
	//print(m);

	
}