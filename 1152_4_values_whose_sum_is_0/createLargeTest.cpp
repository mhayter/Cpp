#include <iostream>
#include <cstdlib>
using namespace std;

int nTests = 20;
int sizeOfTest = 4000;

int main() {
	cout << nTests << endl;
	for(int i=0;i<nTests;i++) {
		cout << sizeOfTest << endl;
		for(int i=0;i<sizeOfTest;i++) {
			for(int j=0;j<4;j++) {
				cout << rand() << " ";
			}
			cout << endl;
		}
	}
	return 0;
}