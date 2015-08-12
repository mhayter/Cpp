#include <bits/stdc++.h>
using namespace std;

int N;
const int SIZE = 30;
int grid[30];
atomic<int> nSols;

mutex solsMutex;

int allOn;

void dfs(int col,int rowUsed,int upDiag,int downDiag) {
	if (col==N) {
		{
			//lock_guard<mutex>myLock(solsMutex);
			++nSols;
		}
		return;
	}
	//updiag [row+col] = true; downDiag[N+row-col]=true
	int used = rowUsed| (upDiag)>>(col) | downDiag>>(N-col) | grid[col];
	int available = ~used & allOn; // get first N bits

	while(available) {
		//get nex availble bit 
		int lsb = available & (-available);
		dfs(col+1,rowUsed|lsb,upDiag|(lsb<<col), downDiag|(lsb<<(N-col)));
		available &= ~lsb;
	}
}

void multiDfsSetup(int i) {
	int lsb = (1<<i);
	int col = 0;
	dfs(col+1, lsb, lsb << col, lsb << (N-col));
}

void multiDfs() {
	vector<thread>threads;
	for(int i=0;i<N;i++) {
		if ((grid[0] & (1<<i))==0)
			threads.push_back(thread(multiDfsSetup,i));
	}
	for(auto &x:threads) {
		x.join();
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

		multiDfs();
		//dfs(0,0,0,0);
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
		//break;
	}
	return 0;
}