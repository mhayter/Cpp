#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int NUM_CASES;

int main(int argc, char*argv[]) {
	if (argc !=2) 
		NUM_CASES = 100;
	else NUM_CASES = atoi(argv[1]);
	
	cout << NUM_CASES << endl << endl;

	int grid[16]={0};

	for(int i=0;i<16;i++) {
		grid[i]=i;
	}

	for(int caseNum=1; caseNum<=NUM_CASES;caseNum++) {
		random_shuffle(grid,grid+16);
		for(int i=0;i<4;i++) {
			for(int j=0;j<4;j++) {
				cout << grid[i*4+j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}