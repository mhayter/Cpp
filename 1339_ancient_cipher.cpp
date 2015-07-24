#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string a,b;
	while (cin>>a>>b){
		vector<int>cnt1(30,0);
		vector<int>cnt2(30,0);

		for(auto &x:a) cnt1[x-'A']++;
		for(auto &x:b) cnt2[x-'A']++;

		sort(cnt1.begin(),cnt1.end());
		sort(cnt2.begin(),cnt2.end());

		if (cnt1 == cnt2) cout << "YES\n";
		else cout << "NO\n";

	}
	return 0;
}