#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int memo[300][300];
int LCS(int i, int j,vector<int> &a, vector<int> &b) {
	if (i<0 || j<0) return 0;
	if (memo[i][j] != -1) return memo[i][j];
	if (a[i] == b[j]) {
		//cout <<a[i] << endl;
		return memo[i][j] = LCS(i-1,j-1,a,b)+1;
	} // take it
	return memo[i][j] = max(LCS(i-1,j,a,b), LCS(i,j-1,a,b));
}

int LCSLen(vector<int> &a, vector<int> &b) {
	vector<vector<int>>C (b.size()+1, vector<int>(a.size()+1));

	for(int i=0;i<=a.size();i++) 
		C[i][0] = 0;
	for(int j=0;j<=b.size();j++) {
		C[0][j] = 0;
	}

	a.insert(a.begin(),0);
	b.insert(b.begin(),0);
	for (int i=1; i<=a.size();i++) {
		for (int j=1;j<=b.size();j++) {
			if (a[i] == b[i]) {
				C[i][j] = C[i-1][j-1] + 1;
			} else {
				C[i][j] = max(C[i][j-1], C[i-1][j]);
			}
		}
	}
	return C[(int)a.size()-1][(int)b.size() -1];
}


int main() {
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		int n, p, q; cin >> n >> p >> q;
		for(int i=0;i<300;i++)for(int j=0;j<300;j++) memo[i][j] = -1;
		vector<int> a(++p), b(++q);

		//for(int i=0;i<p;i++) cin >> a[i];
		//for(int i=0;i<q;i++) cin >> b[i];

		//get longes common subsequence

		for(auto x:a) cout << x << " "; cout << endl;
		for(auto x:b) cout << x << " "; cout << endl;

		int ans = LCS(p-1,q-1,a,b);
		cout << "Case " << caseNum << ": " << ans <<"\n";
	}
	return 0;
}