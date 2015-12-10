#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int>a;

void genNum(long long num) {
	if (num>1e9) {
		return;
	}
	a.push_back(num);
	genNum(num*10+4);
	genNum(num*10+7);
}

int main() {
	genNum(0);
	sort(a.begin(),a.end());
	int n; cin >>n;
	for(int i=0;i<a.size();i++) {
		cerr <<"i = " << a[i]<< endl;
		if (a[i] == n) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}