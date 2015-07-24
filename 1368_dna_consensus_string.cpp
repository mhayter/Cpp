#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int N; cin >>N;
	for(int caseNum=1;caseNum<=N;caseNum++) {
		int n, m; cin >> n >> m;
		vector<string>a(n);
		for(int i=0;i<n;i++) {
			cin >> a[i];
		}
		string ans;
		int diff = 0;
		for (int j=0;j<m;j++) {
			//get most frequent
			int A,C,G,T;
			A=C=G=T=0;
			for(int i=0;i<n;i++) {
				if (a[i][j] == 'A') A++;
				if (a[i][j] == 'C') C++;
				if (a[i][j] == 'G') G++;
				if (a[i][j] == 'T') T++;
			}

			int mx = max(A,max(C,max(G,T)));
			if (mx == A) {
				ans+="A";
			} else if (mx == C) {
				ans += "C";
			} else if (mx == G) {
				ans += "G";
			} else ans += "T";

			diff += n - mx;
		}
		cout << ans << "\n" << diff <<"\n";
	}
	return 0;
}