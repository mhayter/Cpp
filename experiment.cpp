#include <iostream>
#include <map>
//#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lambda/lambda.hpp>
using namespace std;
/*void f1(int **p){
 f2(p);
}
void f2(int **p){
 *p = new int(4);

}
*/

void f(int *&p) {
	int c = 5;
	std::cerr << &c << std::endl;
	p = &c;
}

template <class T>
int sizeOf(T) {
	T a[2];
	return (char *)(&a[1]) - (char *)(&a[0]);
}

struct State {
	char c[9];
	double b;
	int d;
};

int main(){

	using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );

   	namespace mp = boost::multiprecision;

   	mp::int128_t a(3);
   	

 int *p;
 *p = 2234;
 int  *a;
 f(a);
 
 std::cout << "before " << std::endl;
 std::cout << "*a = " << a <<" " <<*a <<std::endl;
 
 int *ptr = (int*)0x23caac;
 map<int,int>myMap;
 for(int i=0;i<1000;i++) {
 	myMap[*ptr]++;
 	if (*ptr !=0) {
 		std::cout << ptr << " " << *ptr <<std::endl;
 	}
 	++ptr;
 }

 /*for(auto &x:myMap) {
 	cout << x.first << " " << x.second << endl;
 }
 */
 std::cout << *ptr << std::endl;
 
 int *z = new int[1000];
 cout << z << endl; 
 long long ans = 4 * (z-ptr);
 cout << (int *)&z - z << " ";
 cout << (z-ptr) << "bytes diff :"<< ans <<" equals " <<ans/1024 << " kb " << ans/(1024*1024) <<" MB "<< ans/(1024*1024*1024)<<" GB"<< endl;
 //f1(&p);
 //std::cout<<*p<<std::endl;
 State f;
 cout << sizeOf(f) << " " << sizeof(State)<< endl;
 return 0;
}
