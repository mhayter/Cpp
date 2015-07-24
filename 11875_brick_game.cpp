#include <iostream>
#include <vector>
using namespace std;

int main() {
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		int n; cin >>n;
		vector<int>a(n);
		for(int i=0;i<n;i++) {
			cin >> a[i];
		}
		cout << "Case " << caseNum << ": "<< a[n/2] << "\n";
	}
	return 0;
}