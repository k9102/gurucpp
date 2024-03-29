#include <iostream>
#include <algorithm>
#include <functional> // less<>, greater<> 이 여기에 있습니다.
using namespace std;

inline bool cmp1(int a, int b) { return a < b; }
inline bool cmp2(int a, int b) { return a > b; }

int main()
{
	int x[10] = { 1,3,5,7,9,2,4,6,8,10 };

	// sort() 함수는 모든 인자가 템플릿 입니다.
	// 1. 비교정책으로 일반 함수를 사용할때

	// 장점 : 비교정책을 교체해도 sort() 기계어 코드는 한개이다.
	//		  코드 메모리 증가 안함
	// 단점 : 비교정책이 인라인 치환될수 없다. 느리다.

	sort(x, x + 10, cmp1); // sort(int*, int*, bool(*)(int,int)) 인 함수 생성
	sort(x, x + 10, cmp2); // sort(int*, int*, bool(*)(int,int)) 인 함수 생성


	// 2. 비교정책으로 함수객체를 사용할때

	// 단점 : 정책을 교체한 횟수 만큼 sort 기계어 코드 생성
	//		코드메모리 증가

	// 장점 : 정책 함수의 내용이 인라인 치환된다. 빠르다.!!

	less<int> f1;    // STL 안에 이 함수객체가 있습니다.
	greater<int> f2;

	sort(x, x + 10, f1); // sort(int*, int*, less<int> ) 인 함수 생성
	sort(x, x + 10, f2); // sort(int*, int*, greater<int>) 인 함수 생성
}




