#include <iostream>
#include <vector>
#include <map>
using namespace std;

int N, nQueries;
vector<int>a;

int main() {
	cin >> N >> nQueries;
	for(int i=0;i<N;i++) {
		int num; cin >> num;
		a.push_back(num);
	}

	for(int i=0;i<nQueries;i++) {
		int start, end;
		cin >> start >> end;
		--start;--end;
		
		int ind = start;
		int mx = 0;
		while (ind <= end) {
			int newInd = (int)(upper_bound(a.begin()+ind,a.begin()+end+1,a[ind]) - a.begin());
			int diff = newInd - ind;
			ind =  newInd;
			mx = max(diff,mx);
		}
		cout << mx << endl;

	}
	return 0;
}
