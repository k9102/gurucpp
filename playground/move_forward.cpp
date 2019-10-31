#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <type_traits>

using namespace std;

/*
T is deduced
T&& is a forwarding reference
*/
template<typename T> remove_reference_t<T>&& xmove(T&&t)
{
	return static_cast<remove_reference_t<T>&&>(t);
}



/*
T is not deduced.
That is why xforward is implemented  for rvalue and lvalue respectively
T&& is rvlaue reference
*/
template<typename T> T&& xforward(remove_reference_t<T>&t)
{
	return static_cast<T&&>(t);
}

template<typename T> T&& xforward(remove_reference_t<T>&&t)
{
	return static_cast<T&&>(t);
}


/*chronometry is added for the sake of test*/
template<typename F, typename...Ts> decltype(auto) chronometry_(F&& f, Ts&&...args)
{
	cout << __FUNCSIG__ << endl;

	auto s = std::chrono::high_resolution_clock::now();

	decltype(auto) ret = xforward<F>(f)(xforward<Ts>(args)...);

	auto e = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> etm = e - s;
	std::cout << "Elapsed time = " << etm.count() * 1000 << "ms" << endl;

	return static_cast<decltype(ret)>(ret);
}


int g_ = 0;
volatile int sink;
int& Test(int limits)
{
	for (auto size = 1; size < limits; size *= 100)
	{
		std::vector<int> v(size, 42);
		sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
	}

	return g_;
}

int main()
{
	chronometry_(Test, 10000) = 5;
	
	cout << g_ << endl;
}