#include <iostream>

using namespace std;


template<typename T> struct xfunction;
template<typename T, typename...Ts> struct xfunction<T(Ts...)>
{

	struct IFunc
	{
		virtual T operator()(Ts...args) = 0;
		virtual ~IFunc() = default;
	};

	/*funciton pointer*/
	struct Func :public IFunc
	{
		T(*f_)(Ts...);

		Func(T(*f)(Ts...)) :f_(f) {};
		T operator()(Ts...args) override { 
			if constexpr (is_same_v<T, void>)
				f_(args...);
			else
				return f_(args...);
		};

	};
	/*funciton object*/
	template<typename U> struct FunObj:public IFunc
	{
		U fo_;

		FunObj(U fo) :fo_(fo) {};
		T operator()(Ts...args) override { 
			if constexpr (is_same_v<T, void>)
				fo_(args...);
			else
				return fo_(args...); 
		};
	};

	/*member funcion*/
	template<typename U> struct MemFunc :public IFunc
	{
		T(U::*f_)(Ts...);
		U *obj_;
		MemFunc(T(U::*f)(Ts...),U *obj) :f_(f),obj_(obj) {};
		T operator()(Ts...args) override { 
			if constexpr (is_same_v<T, void>)
				(obj_->*f_)(args...);
			else
				return (obj_->*f_)(args...); 
		};
	};
	
	unique_ptr<IFunc> func_;

	xfunction(T(*f)(Ts...)) :func_(new Func(f)) {};
	template<typename U> xfunction(U u): func_(new FunObj<U>(u)){}
	template<typename U> xfunction(T(U::*f_)(Ts...), U *obj): func_(new MemFunc<U>(f_, obj)) {}

	T operator()(Ts...args) {
		if constexpr (is_same_v<T,void>)
			(*func_)(args...);
		else
			return (*func_)(args...);
	}

};


class Test
{
public:
	void Print(int a)
	{
		cout << __FUNCSIG__ << endl;
		cout << a << endl;
	}
};

void print(int  a)
{
	cout << __FUNCSIG__ << endl;
	cout << a << endl;
}

int main()
{
	xfunction<void(int)> f0(print);
	xfunction<void(int)> f1([](int a) {
		cout << __FUNCSIG__ << endl;
		cout << a << endl;
	});

	
	f0(10);
	f1(100);

	Test obj;
	xfunction<void(int)> f2(&Test::Print,&obj);

	f2(1000);

	return 0;
}