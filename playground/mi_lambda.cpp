
#include <iostream>


using namespace std;

/*
Make a multi parameter interface
*/
template<typename...Ts> class Mi :public Ts...
{
public:
	using Ts::operator()...;
	Mi(Ts...args):Ts(args)... {};
};



int main()
{

	Mi la
	(
		[](int a, int b) {return a + b; }, 
		[](int a, int b, int c) {return a + b + c; }
	);

	cout << la(1, 2,3) <<endl;

	return 0;
}