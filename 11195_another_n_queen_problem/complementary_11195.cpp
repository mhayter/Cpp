#include <bits/stdc++.h>
using namespace std;

int N;
int NminusOne;
const int SIZE = 15;
int grid[SIZE];
int nSols;

int allOn;

int sp=0;
int sta[4*32*SIZE];
int *ptr;

void dfs2(int col,int rowUsed,int upDiag,int downDiag) {
	ptr = sta;
	*(ptr++) = col;
	*(ptr++) = rowUsed;
	*(ptr++) = upDiag;
	*(ptr++) = downDiag;

	while (ptr != sta) {
		downDiag = *(--ptr);
		upDiag = *(--ptr);
		rowUsed = *(--ptr);
		col = *(--ptr);

		//cout << col << endl;

		if (col==N) {++nSols;continue;}
		//updiag [row+col] = true; downDiag[N+row-col]=true
		int used = rowUsed| (upDiag)>>(col) | downDiag>>(N-col) | grid[col];
		int available = ~used & allOn; // get first N bits

		while(available) {
			//get nex availble bit 
			//int lsb = ((available-1)&available)^available;
			int lsb = available & (-available);
			//cout << "row " << lsbIndex << " col " << col << endl;
			//if (col == NminusOne) { ++nSols;}
			//else {
				*(ptr++) = col+1;
				*(ptr++) = rowUsed|lsb;
				*(ptr++) = upDiag|(lsb<<col);
				*(ptr++) = downDiag|(lsb<<(N-col));
			//}

			available &= ~lsb;
		}

	}
}
pair<int,int>cols[SIZE];
pair<int,int>rows[SIZE];

int c[SIZE+5];
int r[SIZE+5];

int colGrid[SIZE];
int rowGrid[SIZE];

void dfs(int colIndex,int col, int rowUsed,int upDiag,int downDiag,const int *next,const int *grid) {
	if (colIndex==N) {++nSols;return;}
	//lookahead
	/*for(int i=col;i<N;++i) {
		int used = rowUsed| (upDiag)>>(i) | downDiag>>(N-i) | grid[i];
		int available = ~used & allOn;
		if (!available) return;
	}
	*/
	//updiag [row+col] = true; downDiag[N+row-col]=true
	int used = rowUsed| (upDiag)>>(col) | downDiag>>(N-col) | grid[col];
	int available = ~used & allOn; // get first N bits

	while(available) {
		//get nex availble bit 
		//int lsb = ((available-1)&available)^available;
		int lsb = available & (-available);
		//cout << "row " << lsbIndex << " col " << col << endl;
		dfs(colIndex+1,next[colIndex+1],rowUsed|lsb,upDiag|(lsb<<col), 
			downDiag|(lsb<<(N-col)), next, grid);

		available &= ~lsb;
	}
}



bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
	if (a.first > b.first) return true;
	return false;
}

int doComplement(const vector<pair<int,int>> &badSquares,const int *next,int *grid) {
	int n = badSquares.size();
	int totSols = 0;
	for(int i=1;(1<<n);i++) {
		int num = i;
		vector<int>indexes;
		while (num) {
			int index = __builtin_ffs(num) - 1;
			indexes.push_back(index);
			num &= (num-1);
		}
		for(auto &x:indexes) {
			int row = badSquares[x].first;
			int col = badSquares[x].second;
			grid[row] ^= (1<<col);
		}
		nSols = 0;
		dfs(0,c[0],0,0,0,c,grid);
		totSols+=nSols;
		for(auto &x:indexes) {
			int row = badSquares[x].first;
			int col = badSquares[x].second;
			grid[row] ^= (1<<col);
		}
	}
}


int main() {
	int caseNum=1;
	//ios_base::sync_with_stdio(false);
	while (true) {
		cin >> N;
		NminusOne = N-1;
		if (N==0) break;
		nSols=0;
		allOn = (1<<N) - 1;
		for(int i=0;i<N;++i) colGrid[i]=rowGrid[i]=0;
		vector<pair<int,int>> badSquares;
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				char c;
				cin >> c;
				if (c=='*')	{
					colGrid[j] |= (1<<i);
					rowGrid[i] |= (1<<j);
					badSquares.push_back(make_pair(i,j));
				}
			}
		}

		//find best row first or col first
		for(int i=0;i<N;i++) {
			cols[i]=make_pair(__builtin_popcount(colGrid[i]),i);
			rows[i]=make_pair(__builtin_popcount(rowGrid[i]),i);
		}

		sort(cols,cols+N,cmp);
		sort(rows,rows+N,cmp);

		for(int i=0;i<N;++i){ 
			c[i] = cols[i].second;
			r[i] = rows[i].second;
		}

		//cout << "N = " << N << endl;
		/*for(auto &x:cols) 
			cout << x.first << " " << x.second << endl;
		cout << "cols[0] " << cols[0].second << endl; 
		cout << bitset<32>(grid[c[0]]) << endl;
		*/
		doComplement(badSquares,c,colGrid);
		/*
		if (r[0] > c[0])
			dfs(0,r[0],0,0,0,r,rowGrid);
		else dfs(0,c[0],0,0,0,c,colGrid);
		*/
		cout << "Case "<<caseNum++<<": "<<nSols << endl;
	}
	return 0;
}