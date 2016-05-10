#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int SIZE = 20;
ll memo[SIZE][SIZE];

ll n, an1;

ll a(int i, int j) {
	if (i == n && j == 1) return an1;
	if (memo[i][j] != -1) return memo[i][j];
	if (i >= j) {
		ll num1 = 0;
		if (i < n){
			for(int k=i+1;k<=n;k++) {
				num1 = max(num1,a(k,1)+a(k,j));
			}
		} else if (i==n) {
			num1 = 0;
		} else {
			cerr << "i doesn't fit " << i << endl;
		}

		ll num2 = 0;

		if(j>0) {
			for(int k=1;k<j;k++) {
				num2 = max(num2, a(i,k)+a(n,k));
			}
		} else if (j == 0) {
			num2 = 0;
		} else {
			cerr << "j doesn't fit " << j << endl;
		}
		return memo[i][j] = num1+num2;
	} else {
		ll myMaxSum = 0;
		for(int k=i;k<j;k++) {
			myMaxSum = max(myMaxSum, a(i,k) + a(k+1,j));
		}
		return memo[i][j] = myMaxSum;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> n >> an1) {
		for(int i=0;i<=n;i++) 
			for(int j=0;j<=n;j++)
				memo[i][j] = -1;
		//memset(memo, -1, sizeof(memo));
		memo[n][1] = an1;

		cout << a(1,n) << "\n";
	}
	return 0;
}