#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

const int BASE = 27;

int main() {
	ios_base::sync_with_stdio(false);
	int passwordLength; string s;
	vector<long long> power;
	long long value =1;
	for(int i=0;i<=10;i++) {
		power.push_back(value);
		value*=BASE;
	}
	while (cin >> passwordLength >> s) {
		unordered_map<long long,int>myMap;
		myMap.reserve(s.size());

		int curMax  = 0;
		int ansPlace = 0;
		//buld string (assuming passowdlengh < s.leng)

		long long hash = 0;
		for(int i=0;i<passwordLength;i++) {
			hash = hash*BASE + s[i]-'a'+1;
		}

		myMap[hash]++;
		curMax = 1;

		//cerr << "hash " << hash << endl;
		int place = 0;
		for(int i=passwordLength;i<s.size();i++) {
			//cerr << "power " << power[passwordLength-1] << endl;
			hash -= power[passwordLength-1]*(s[place++]-'a'+1);
			//cerr << "After sub " << hash << endl;
			hash *= BASE;
			//cerr << "AFter base " << hash << endl;
			hash += s[i]-'a'+1;
			//cerr <<"Inside hash = " << hash << endl;
			//cerr << "curStr = " << curStr << endl;
			int num = ++myMap[hash];
			if (num > curMax) {
				curMax = num;
				ansPlace = place;
				//cerr << "new ans = " << ansPlace <<" num = " << num << endl;
			}
		}
		for(int i=ansPlace, nTimes=0;nTimes<passwordLength;i++,nTimes++){
			cout << s[i];
		}
		cout << "\n";
	}
	return 0;
}