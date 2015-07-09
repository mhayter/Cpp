#include <bits/stdc++.h>
using namespace std;

int N;

int grid[15];
int nSols;

int allOn;

void dfs(int col,int rowUsed,int upDiag,int downDiag) {
	if (col==N) {++nSols;return;}
	//updiag [row+col] = true; downDiag[N+row-col]
	int used = rowUsed| (upDiag)>>(col) | downDiag>>(N-col) | grid[col];
	int available = ~used & allOn; // get first N bits

	while(available) {
		//get nex availble bit 
		//int lsb = ((available-1)&available)^available;
		int lsb = available & (-available);
		//cout << "row " << lsbIndex << " col " << col << endl;
		dfs(col+1,rowUsed|lsb,upDiag|(lsb<<col), downDiag|(lsb<<(N-col)));

		available &= ~lsb;
	}
}


int main() {
	int caseNum=1;
	while (true) {
		cin >> N;
		if (N==0) break;
		nSols=0;
		allOn = (1<<N) - 1;
		for(int i=0;i<N;++i) grid[i]=0;
		
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				char c;
				cin >> c;
				if (c=='*')	grid[j] |= (1<<i);
			}
		}
		//cout << "N = " << N << endl;
		dfs(0,0,0,0);
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
	}
	return 0;
}