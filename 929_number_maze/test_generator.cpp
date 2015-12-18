#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	int nRows = 1000;
	int nCols = 1000;

	cout << nRows << endl << nCols << endl;
	for (int i=0;i<nRows;i++) {
		for(int j=0;j<nCols;j++) {
			cout << rand()%10 + 1 << " ";
		}
		cout << endl;
	}
	return 0;
}