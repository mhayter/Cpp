#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	int n = 1000000;
	cout << n << endl;
	for(int i=0;i<n;i++) {
		cout << rand()%(100+1) << "\n";
	}
	return 0;
}