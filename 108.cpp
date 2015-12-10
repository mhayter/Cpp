#include <iostream>
#include <algorithm>
using namespace std;

//not done

const int SIZE = 110;
int grid[SIZE][SIZE];
const int INF = 1000000000;
int memo[SIZE/2][SIZE/2][SIZE/2][SIZE/2];
int N;

int getSum(int i,int L,int j,int L2) {
	/*if (i<SIZE/2 && j<SIZE/2 && L<SIZE/2 && L2<SIZE/2) {
		if (memo[i][L][j][L2] !=-INF) return memo[i][L][j][L2];
	}*/
	int sum = 0;
	for(int k=i,nTimes=1;nTimes<=L;nTimes++,k++) {
		for(int m=j,nTimes2=1;nTimes2<=L2;nTimes2++,m++) {
			sum+=grid[k][m];
		}
	}
	return memo[i][L][j][L2]=sum;
}

void resetMemo() {
	int SZ = N/2;
	for(int i=0;i<SZ;i++) {
		for(int j=1;j<=SZ;j++) {
			for(int k=0;k<SZ;k++) {
				for(int m=1;m<=SZ;m++) {
					memo[i][j][k][m] = -INF;
				}
			}
		}
	}
}

int getMaxRectangle() {
	int ans = -1000000000;
	resetMemo();
	for(int L = 1; L<=N;L++) {
		for(int L2=1; L2<=N;L2++) {
			for(int i=0;i+L<=N;i++) {
				for(int j=0;j+L2<=N;j++) {
					//get sum;
					int sum = getSum(i,L,j,L2);
					ans = max(ans,sum);
				}
			}
		}
	}
	return ans;
}

int main() {
	cin >> N;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cin >> grid[i][j];
		}
	}
	cout << getMaxRectangle() << endl;
	return 0;
}