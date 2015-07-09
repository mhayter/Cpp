#include <bits/stdc++.h>
using namespace std;

int N;

char grid[15][15];
int nSols;

bool rowUsed[15];
bool upDiag[30];
bool downDiag[30];

bool isValid(int row,int col) {

	if (rowUsed[row]) return false;
	if (upDiag[row+col]) return false;
	if (downDiag[N+row-col]) return false;
	if (grid[row][col]=='*') return false;
	return true;
}

void mark (int row,int col) {
	rowUsed[row]=upDiag[row+col]=downDiag[N+row-col]=true;
}
void unMark(int row,int col) {
	rowUsed[row]=upDiag[row+col]=downDiag[N+row-col]=false;
}

void dfs(int col) {
	if (col==N) {nSols++;return;}
	for(int row=0;row<N;++row) {
		if(isValid(row,col)) {
			mark(row,col);
			dfs(col+1);
			unMark(row,col);
		}
	}
}


int main() {
	int caseNum=1;
	while (true) {
		cin >> N;
		if (N==0) break;
		nSols=0;
		for(int i=0;i<N;i++) {
			rowUsed[i]=false;
			for(int j=0;j<N;j++) {
				cin >> grid[i][j];
				//cout << "grid " << grid[i][j] << endl;
				upDiag[i+j]=false;
				downDiag[N+i-j] = false;
			}
		}
		//cout << "N = " << N << endl;
		dfs(0);
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
	}
	return 0;
}