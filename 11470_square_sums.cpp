#include <iostream>
using namespace std;

//#1 tied (206) 8/12/2015 no count

int grid[100][100];

int main() {
	int n; 
	int caseNum=1;
	while (cin >> n) {
		if (n==0) break;
		cout << "Case " << caseNum++ << ": ";
		int sum = 0;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cin >> grid[i][j];
			}
		}
		int sx=0, sy = 0;
		int ex=n-1, ey = n-1; 
		for(int len=n;len>0;len-=2) {
			sum =0;
			//go right
			for(int i=sx;i<=ex;i++) {
				sum+=grid[sy][i];
			}
			//down
			for(int i=sy+1;i<ey;i++) sum+=grid[i][sx];
			//left
			if (sx!=ex)
			for(int i=sx;i<=ex;i++) {
				sum+=grid[ey][i];
			}
			//up	
			for(int i=sy+1;i<ey;i++) sum+=grid[i][ex];

			cout << sum;
			if (len == 1 || len==2) cout << endl;
			else cout << " ";

			++sx;
			++sy;
			--ex;
			--ey;
		}
	}
	return 0;
}