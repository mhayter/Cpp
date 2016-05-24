#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

//reserved outside and cleared 0.0900s!

//record holder 5/24/2016 0.100s


const int HASH_TABLE_SIZE = 1 << 19;
vector<pair<long long,int>> myTable[HASH_TABLE_SIZE];
vector<int>clearHashes;

int getValue(long long longHash) {
	int hash = longHash & (HASH_TABLE_SIZE - 1);
	//find it in the table
	if (myTable[hash].size() == 0) {
		myTable[hash].emplace_back(make_pair(longHash,1));
		clearHashes.emplace_back(hash);
		return 1;
	} else {
		//check if it's contained
		for(int i=0;i<myTable[hash].size();i++) {
			if (myTable[hash][i].first == longHash) {
				return ++myTable[hash][i].second;
			} 
		}
		myTable[hash].emplace_back(make_pair(longHash,1));
		return 1;
	}
}

const int BASE = (1<<5)-1;
//unordered_map<long long,int>myMap;
const int MAX_STRING_SIZE = 1000010;
int main() {
	ios_base::sync_with_stdio(false);
	int passwordLength; string s;
	vector<long long> power;
	long long value =1;
	for(int i=0;i<=10;i++) {
		power.push_back(value);
		value*=BASE;
	}
	//myMap.reserve(MAX_STRING_SIZE);
	while (cin >> passwordLength >> s) {
		//if (s.size() > MAX_STRING_SIZE) throw -1;
		//myMap.clear();
		for(int i=0;i<clearHashes.size();i++) myTable[clearHashes[i]].clear();

		int curMax  = 0;
		int ansPlace = 0;
		//buld string (assuming passowdlengh < s.leng)

		long long longHash = 0;
		for(int i=0;i<passwordLength;i++) {
			longHash = longHash*BASE + s[i]-'a'+1;
		}
		curMax = 1;

		//cerr << "hash " << hash << endl;
		int place = 0;
		for(int i=passwordLength;i<s.size();i++) {
			//cerr << "power " << power[passwordLength-1] << endl;
			longHash -= power[passwordLength-1]*(s[place++]-'a'+1);
			//cerr << "After sub " << hash << endl;
			longHash *= BASE;
			//cerr << "AFter base " << hash << endl;
			longHash += s[i]-'a'+1;
			int num;
			int hash = longHash & (HASH_TABLE_SIZE - 1);

			//find it in the table
			if (myTable[hash].size() == 0) {
				myTable[hash].emplace_back(make_pair(longHash,1));
				clearHashes.emplace_back(hash);
				num = 1;
			} else {
				//check if it's contained
				for(int i=0;i<myTable[hash].size();i++) {
					if (myTable[hash][i].first == longHash) {
						num =  ++myTable[hash][i].second;
						goto done;
					} 
				}
				myTable[hash].emplace_back(make_pair(longHash,1));
				num = 1;
			}
			done:;
			//cerr <<"Inside hash = " << hash << endl;
			//cerr << "curStr = " << curStr << endl;
			//int num = ++myMap[hash];
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