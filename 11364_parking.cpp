#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

//tied #1 (450) 0.000s

int main() {
	int nCases; cin >> nCases;
	for (int caseNum=1;caseNum<=nCases;caseNum++) {
		int n; cin >> n;
		vector<int>a(n);
		for(auto &x:a) cin >> x;

		sort(a.begin(),a.end());

		int ans=0;
		int prev = a[0];
		for(int i=1;i<a.size();i++) {
			ans += a[i] - prev;
			prev = a[i];
		}
		ans+=a[n-1]-a[0];
		cout << ans << endl;
	}
	return 0;
}