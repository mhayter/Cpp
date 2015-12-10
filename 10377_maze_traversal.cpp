#include <iostream>
using namespace std;

//tied #1 8/12/2015 (128) 0.000s doesn't count

const int SIZE = 70;

char grid[SIZE][SIZE];
int nRows,nCols;
int ry,rx;
char rDir;

char dirs[] = "NESW";
int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};

bool isValid(int y,int x) {
	if (y<0 || y>=nRows || x<0 || x>=nCols) return false;
	if (grid[y][x]!=' ') return false;
	return true;
}

int getDirInd() {
	for(int i=0;i<4;i++) {
		if (dirs[i]==rDir) {
			return i;
		}
	}
	return -1;
}

int main() {
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		cin >> nRows >> nCols;
		string line; getline(cin,line); //space;
		for(int i=0;i<nRows;i++) {
			getline(cin,line);
			for(int j=0;j<nCols;j++) {
				grid[i][j] = line[j];
			}
		}
		cin >> ry >> rx;
		--ry; --rx;
		rDir = 'N';

		char command;
		while (cin>>command && command!='Q') {
			if (command == 'F') {
				//go foward
				int ind = getDirInd();
				int ny = ry+dy[ind];
				int nx = rx+dx[ind];
				if (isValid(ny,nx) ) {
					ry=ny;
					rx=nx;
				}
			} else if (command == 'L') {
				//turn left
				int ind = getDirInd()-1;
				if (ind <0) ind = 3;
				rDir = dirs[ind];

			} else {
				//turn right
				int ind = (getDirInd()+1)%4;
				rDir = dirs[ind];
			}
		}
		cout << ry+1 << " " << rx+1 <<" " << rDir << endl;
		if (caseNum != nCases) cout << endl;

	}
}