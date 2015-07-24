#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N=8;

int curSol[N];
int nSols;

vector<vector<int>>sols;

void dfs(int col, int rowAvail, int diag1, int diag2) {
	if (col == N) {
		//sol ound
		vector<int> newSol (curSol,curSol+N);
		sols.push_back(newSol);
		++nSols;
		return;
	}
	int avail = rowAvail & diag1 & diag2;

	while (avail) {
		int index = __builtin_ctz(avail);

		curSol[col] = index;
		int lsb = avail & -avail;

		dfs(col+1, rowAvail^lsb, ((diag1^lsb) << 1)|1, (diag2^lsb) >> 1);
		avail ^= lsb;
	}

}

int main() {
	dfs(0,(1<<N)-1, (1<<N)-1, (unsigned)-1);
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int caseNum = 1; caseNum<=nCases;caseNum++) {
		cout << "SOLN       COLUMN\n";
		cout << " #      1 2 3 4 5 6 7 8\n\n";

		int Qr,Qc; cin >> Qr >> Qc;
		--Qr; --Qc;
		int nAns = 1;
		for(int i=0;i<sols.size();i++) {
			if (sols[i][Qc]==Qr){
				if (nAns < 10) cout <<" ";
				cout << nAns++ << "      ";
				for(int j=0;j+1<sols[i].size();j++) {
					cout << sols[i][j] + 1<< " ";
				} 
				cout << sols[i][7]+1 << endl;
			}
		}
		if (caseNum != nCases) cout << endl;
	}
	return 0;
}