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
#include <type_traits>

using namespace std;
using namespace std::placeholders;


template<typename R, typename...ARG> class IFunc
{
public:
	virtual R operator()(ARG...) = 0;
	virtual IFunc *clone() = 0;
	virtual ~IFunc() = default;
};

template<typename R, typename...ARG> class GenFunc :public IFunc<R, ARG...>
{
	R(*f_)(ARG...);
public:
	GenFunc(R(*f)(ARG...))
	{
		f_ = f;
	}
	virtual R operator()(ARG...args) override
	{
		if constexpr (!is_same_v<R, void>)
			return f_(args...);
		else
			f_(args...);

	}
	virtual IFunc<R, ARG...> *clone() override { return(new GenFunc(*this)); }
	virtual ~GenFunc() { cout << __FUNCSIG__ << endl; };
};

template<typename T, typename R, typename...ARG> class MemFunc :public IFunc<R, ARG...>
{
	R(T::*f_)(ARG...);
	T *obj_;
public:
	MemFunc(R(T::*f)(ARG...), T *obj)
	{
		f_ = f;
		obj_ = obj;
	}
	virtual R operator()(ARG...args) override
	{
		if constexpr (!is_same_v<R, void>)
			return (obj_->*f_)(args...);
		else
			(obj_->*f_)(args...);
	}
	virtual IFunc<R, ARG...> *clone() override { return (new MemFunc(*this)); }
	virtual ~MemFunc() { cout << __FUNCSIG__ << endl; };
};

template<typename T> class Func;
template<typename R, typename...ARG> class Func<R(ARG...)>
{
public:

	template<typename P>  using mtype = R(P::*)(ARG...);
	using ftype = R(*)(ARG...);
	unique_ptr<IFunc<R, ARG...>> f_;

	R operator()(ARG...args)
	{
		if constexpr (!is_same_v<R, void>)
			return (*f_)(args...);
		else
			(*f_)(args...);
	}

	Func(ftype f) :f_(new GenFunc<R, ARG...>(f))
	{
	}

	template<typename T> Func(R(T::*f)(ARG...), T* p) : f_(new MemFunc<T, R, ARG...>(f, p))
	{
	}

	Func& operator=(const Func &r) { f_.reset(r.f_->clone()); return *this; }
};

void foo(int a, double b)
{
	cout << __FUNCSIG__ << endl;
}

class Cls
{

public:
	void goo(int a, double b)
	{
		cout << __FUNCSIG__ << endl;
	}
};

#include <chrono>
#include <ctime>
int main()
{
	char x[10] = "geary";
	Func<void(int, double)> f(&foo);

	f(1, 2);
	Cls obj;

	Func<void(int, double)> g(&Cls::goo, &obj);

	g(1, 2);

	f = g;
}