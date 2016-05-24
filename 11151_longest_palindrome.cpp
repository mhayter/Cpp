#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int SIZE = 1010;
int memo[SIZE][SIZE];
string s;

int maxPal(int left, int right) {
	if (left == right) return 1;
	if (left > right) return 0;
	int &ret = memo[left][right];
	if (ret != -1) return ret;
	if (s[left] == s[right]) {
		return ret = maxPal(left+1,right-1) + 2;
	} else {
		return ret = max(maxPal(left+1,right), maxPal(left,right-1));
	}
}

int main() {
	int n; cin >> n;getline(cin,s);//blank
	for(int i=0;i<n;i++) {
		getline(cin,s);
		for(int i=0;i<=s.size();i++) {
			for(int j=0;j<=s.size();j++) {
				memo[i][j] = -1;
			}
		}
		cout << maxPal(0,(int)s.size()-1) << "\n";
	}
	return 0;
}