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



class A
{
public:
	string GetName() { return __FUNCSIG__; }
};

class B
{
public:
	string GetName() { return __FUNCSIG__; }
};

class C
{
public:
	string GetName() { return __FUNCSIG__; }
};

class Name
{
public:
	struct Inf
	{
		virtual string GetName() = 0;
	};

	template<typename T> class Wrapper :public Inf
	{
		unique_ptr<T> ptr_;
	public:
		Wrapper(T *ptr) :ptr_(ptr)
		{
		};
		virtual string GetName() override
		{
			return ptr_->GetName();
		}
	};

	string GetName()
	{
		return inf_ptr_->GetName();
	}
	template<typename U> Name(U *pobj) : inf_ptr_{ new Wrapper<U>(pobj) }
	{
	}
private:
	shared_ptr<Inf> inf_ptr_;
};

#include <chrono>
#include <ctime>
int main()
{

	vector<Name> v = { new A,new B,new C };
	for (auto &nm : v)
	{
		std::cout << nm.GetName() << endl;
	}

}