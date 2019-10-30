
#include <iostream>
#include <tuple>


using namespace std;

template<int...is> class idx_seq {};

/*
Complicate the parent class to populate the integer list
Inheritance is very versatile
*/
template<int N, int...is> class idx_helper :public idx_helper<N-1,N-1,is...> {};
template<int...is>  class idx_helper<0, is...>
{
public:
	using type = idx_seq<is...>;
};

template<int N> typename idx_helper<N>::type mk_seq()
{

	cout << __FUNCSIG__ << endl;
	return  idx_helper<N>::type{};
}


template<typename T, int...is> void PrtTupleImpl(T& tp, idx_seq<is...>)
{
	int data[] = { get<is>(tp)... };


	for (auto i : data)
	{
		cout << i << endl;
	}
}

template<typename T, int...is> void PrtTuple(T& tp)
{
	PrtTupleImpl(tp, mk_seq<tuple_size_v<T>>());
}

template<typename...Ts> decltype(auto) mk_tuple(Ts...args)
{
	return tuple<Ts...>(args...);
}

int main()
{
	auto tp = make_tuple(1, 2, 3);
	PrtTuple(tp);
}