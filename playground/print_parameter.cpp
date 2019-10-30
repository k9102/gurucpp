
#include <iostream>

using namespace std;


void print() {}
/*paramter pack:Ts,tails*/
template<typename T, typename...Ts> void  print(T head, Ts...tails)
{
	cout << __FUNCSIG__ << endl;
	cout << head << endl;
	/*parameter expansion*/
	print(tails...);
}

/*
fold expression
*/
template<typename...Ts> void  print_fe(Ts...args)
{
	(cout << ...<< args) << endl;
}

template<typename...Ts> void  add_fe(Ts...args)
{
	cout << ((-55)+...+args) << endl;
}

int main()
{

	print(1, "abc", 1.1, 0x123);
	print_fe(1, "abc", 1.1, 0x123);
	add_fe(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	return 0;
}