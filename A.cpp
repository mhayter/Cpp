#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int n; cin >> n;
	string s; cin >> s;
	int myMap[30]={0};
	for (int i=0;i<n;i++) {
		myMap[toupper(s[i])-'A']++;
	}
	bool worked = true;
	for(int i=0;i<26;i++) {
		if (myMap[i]==false) worked=false;
	}
	if (worked) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
