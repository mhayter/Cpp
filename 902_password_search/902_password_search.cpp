#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int passwordLength; string s;
	while (cin >> passwordLength >> s) {
		unordered_map<string,int>myMap;

		int curMax  = 0;
		string ans;
		//buld string (assuming passowdlengh < s.leng)
		string curStr;
		for(int i=0;i<passwordLength;i++) {
			curStr+=s[i];
		}
		myMap[curStr]++;
		ans = curStr;
		curMax = 1;

		for(int i=passwordLength;i<s.size();i++) {
			curStr.erase(0,1);
			curStr+=s[i];
			//cerr << "curStr = " << curStr << endl;
			int num = ++myMap[curStr];
			if (num > curMax) {
				curMax = num;
				ans = curStr;
				//cerr << "new ans = " << ans << endl;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}