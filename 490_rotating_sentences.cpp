#include <bits/stdc++.h>
using namespace std;

const int SIZE = 110;
char grid[SIZE][SIZE];

int main() {
	vector<string> strings;
	string s;
	getline(cin,s);
	int len = 0;
	while (cin) {
		strings.push_back(s);
		len = max(len,(int)s.size());
		getline(cin,s);
	}
	for(int j=0;j<len;j++) {
		for(int i=(int)strings.size()-1;i>=0;i--) {
			if (j >= strings[i].size()) cout << " ";
			else if (strings[i][j] == ' '){
				cout << " ";
			} 
			else cout << strings[i][j];
		}
		cout << "\n";
	}
	return 0;
}