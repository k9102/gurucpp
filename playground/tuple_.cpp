#include <thread>
#include <functional>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <algorithm>
#include <map>
#include <sstream>
#include <queue>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::placeholders;


#include <chrono>
#include <ctime>
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*primary template*/
template<typename...T> struct ktuple;
template<typename F, typename...T> struct ktuple<F, T...> :public ktuple<T...>
{
	F value;
	ktuple(F f, T...args) :value(f), ktuple<T...>(args...) {};
	ktuple& operator=(const ktuple&) = default;
	/* this operator is defined to accommodate tie operation*/
	template<typename rF, typename...rT> ktuple& operator=(const ktuple<rF, rT...> &a)
	{
		value = a.value;

		static_cast<ktuple<T...>&>(*this) = static_cast<const ktuple<rT...>&>(a);

		return *this;
	}
};
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*recursion end condition*/
template<> class ktuple<>
{
};

/*primary template*/
template<int N, typename T> struct ktuple_element;
template<int N, typename F, typename...T> struct ktuple_element<N, ktuple<F, T...>>
{
	/* tuple type*/
	using ttype = typename ktuple_element< N - 1, ktuple<T...>>::ttype;
	/* element type*/
	using etype = typename ktuple_element< N - 1, ktuple<T...>>::etype;
};

/*recursion end condition*/
template<typename F, typename...T> struct ktuple_element<0, ktuple<F, T...>>
{
	using ttype = ktuple<F, T...>;
	using etype = F;
};
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
template<int N, typename...Arg>
typename ktuple_element<N, ktuple<Arg...>>::etype&
get(ktuple<Arg...> &t)
{
	return static_cast<typename ktuple_element<N, ktuple<Arg...>>::ttype &>(t).value;
};
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
template<typename...T>
ktuple<T&...>
xtie(T&...args)
{
	return ktuple<T&...>(args...);
}



int main()
{
	ktuple<int, double, short> t(1, 1.1, 3);

	cout << get<2>(t) << endl;

	get<2>(t) = 6;

	cout << get<2>(t) << endl;

	int a = 0;
	double b = 0;
	short c = 0;

	xtie(a, b, c) = t;
}
