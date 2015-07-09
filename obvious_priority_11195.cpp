#include <bits/stdc++.h>
using namespace std;

int N;

int grid[15];
int nSols;

int allOn;

int getNext(int colVisited) {
	//get abit
	int lsbIndex = __builtin_ffs(colVisited);
	--lsbIndex;
	return lsbIndex;
}

void dfs(int col,int colVisited,int rowUsed,int upDiag,int downDiag, int nProcessed) {
	if (nProcessed==N) {
		cout << "colVisited " << colVisited << endl;
		++nSols;
		return;
	}
	//updiag [row+col] = true; downDiag[N+row-col]=true
	int used = rowUsed| (upDiag)>>(col) | downDiag>>(N-col) | grid[col];
	int available = ~used & allOn; // get first N bits

	while(available) {
		//get nex availble bit 
		//int lsb = ((available-1)&available)^available;
		int lsb = available & (-available);
		if (nProcessed==1)
		cout << "row " << __builtin_ffs(available)-1<<" col " << col << endl;
		//get next to process
		int nextCol = getNext(colVisited);
		dfs(nextCol, colVisited&~(1<<nextCol),rowUsed|lsb,upDiag|(lsb<<col), downDiag|(lsb<<(N-col)),nProcessed+1);

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
		//find weakest column most bits set (grid[i])
		int colStart = 0;
		int colMax = -1;
		for(int i=0;i<N;i++) {
			if(__builtin_popcount(grid[i]) > colMax ){
				colMax = __builtin_popcount(grid[i]);
				colStart = i;
			}
		}
		cout << colStart << endl;
		dfs(colStart,0x7fff,0,0,0,0);
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
		break;
	}
	return 0;
}