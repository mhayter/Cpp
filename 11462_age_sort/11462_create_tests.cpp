#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	const int CASES = 100000;
	for(int i=0;i<CASES;i++) {
		int nNums = rand() % 31 + 1; // 1 50
		cout << nNums << "\n";
		for(int j= 0; j<nNums;j++) {
			int num = rand() % 99 + 1; // 1 - 99 
			cout << num << " ";
		}
		cout << "\n";
	}
	cout << 0 << endl;
	return 0;
}