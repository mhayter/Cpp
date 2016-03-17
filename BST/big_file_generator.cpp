#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
using namespace std;

const int SIZE = 10000000;
int a[SIZE];

int main(int argc, char *argv[]) {
	// your code goes here
	int nElements = atoi(argv[2]);
	for(int i=0;i<nElements;i++) {
		a[i] = i;
	}
	random_shuffle(a,a+nElements);
	for(int i=0;i<nElements;i++) {
		cout << a[i] << endl;
	}

	return 0;
}