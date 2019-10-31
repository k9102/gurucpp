#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;


/*
TODO
void return types are not taken care of
*/
template<typename F,typename...Ts> decltype(auto) chronometry(F&& f,Ts&&...args)
{
		cout << __FUNCSIG__ << endl;
		
		auto s = std::chrono::high_resolution_clock::now();

		/* "invoke" is used to serialize the call */
		/* return type is preserved through decltype(auto)*/
		decltype(auto) ret = invoke(forward<F>(f), forward<Ts>(args)...);

		auto e = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> etm = e - s;
		std::cout << "Elapsed time = " << etm.count()*1000 << "ms"<<endl;

		/*
		static cast and decltype is used to reinstate the return type
		*/
		return static_cast<decltype(ret)>(ret);
}


template<typename F, typename...Ts> decltype(auto) chronometry_(F&& f, Ts&&...args) 
{
	cout << __FUNCSIG__ << endl;

	auto s = std::chrono::high_resolution_clock::now();

	decltype(auto) ret = forward<F>(f)(forward<Ts>(args)...);

	auto e = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> etm = e - s;
	std::cout << "Elapsed time = " << etm.count() * 1000 << "ms" << endl;

	return static_cast<decltype(ret)>(ret);
}


int g_ = 0;
volatile int sink;
int&& Test(int limits)
{
	for (auto size = 1; size < limits; size *= 100) 
	{
		std::vector<int> v(size, 42);
		sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
	}

	return move(g_);
}


class C {
public:
	int& Test(int limits)
	{
		for (auto size = 1; size < limits; size *= 100)
		{
			std::vector<int> v(size, 42);
			sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
		}

		return g_;
	}
};

int main()
{
	chronometry_(Test,10000);

	C obj;
	chronometry(&C::Test,&obj,10000);
}

