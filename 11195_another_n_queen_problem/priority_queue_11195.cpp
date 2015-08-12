#include <bits/stdc++.h>
using namespace std;

int N;

int grid[15];
int nSols;

int allOn;

struct State{
	int bitCount;
	int col;
	int rowUsed;
	int upDiag;
	int downDiag;
};

bool operator<(const State &lhs,const State &rhs) {
	return lhs.bitCount < rhs.bitCount;
}

void prioritySearch(int col,int rowUsed,int upDiag,int downDiag) {
	set<State> que;

	while (que.empty()) {
		State temp = *que.begin();
		que.erase(que.begin());

		if (temp.col==N) {++nSols;return;}

		int used = temp.rowUsed| (temp.upDiag)>>(col) 
			| temp.downDiag>>(N-col) | grid[col];
		int available = ~used & allOn; // get first N bits

		while(available) {
			//get nex availble bit 
			int lsb = available & (-available);
			que.insert({__builtin_popcount(available),col+1,temp.rowUsed|lsb,
				temp.upDiag|(lsb<<col), temp.downDiag|(lsb<<(N-col))});
			available &= ~lsb;
		}
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
		prioritySearch(0,0,0,0);
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
	}
	return 0;
}