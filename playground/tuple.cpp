#include <iostream>
#include <string>
using namespace std;


template<typename...Ts> class xtuple {};
template<typename T,typename...Ts> class xtuple<T,Ts...>:public xtuple<Ts...>
{
public:
	T d_;
	xtuple(T t, Ts...ts) :d_(t), xtuple<Ts...>(ts...) {}

	/* This is not copy but tie assignment operator */
	template<typename U,typename...Us> xtuple& operator=(xtuple<U, Us...> &tp) 
	{
		d_ = tp.d_;

		static_cast<xtuple<Ts...>&>(*this) = static_cast<xtuple<Us...>&>(tp);

		return *this;
	}

};

template<int N,typename T> class xelement;
template<int N, typename T,typename...Ts> class xelement<N, xtuple<T,Ts...>>:public xelement<N-1, xtuple<Ts...>>
{
};
/*
This can be implement by using nested type but I choose to use inheritance considering semetry with tuple
*/
template<typename T,typename...Ts> class xelement<0, xtuple<T,Ts...>>
{
public:
	/*tuple type*/
	using ttype = xtuple<T,Ts...>;
	/*element type*/
	using etype = T;
};


template<int N,typename T> typename xelement<N, T>::etype& xget(T &tp)
{
	return static_cast<typename xelement<N,T>::ttype*>(&tp)->d_;
}


template<typename...Ts> xtuple<Ts&...> xtie(Ts&...args)
{
	return xtuple<Ts&...>{args...};
}


int main()
{
	xtuple<int, double, string>  tp{ 1,2.0,"abc"};

	cout << xget<2>(tp) << endl;
	xget<2>(tp) = "def";
	cout << xget<2>(tp) << endl;

	int i;
	double d;
	string s;

	xtie(i, d, s) = tp;

	return 0;
}