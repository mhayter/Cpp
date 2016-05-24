//#include <iostream>
//#include <string>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAX_CHARACTERS_IN_FILE = 10000010;
char buff[MAX_CHARACTERS_IN_FILE];

//fastest so far with 0.0800s for some reaons 10M char buff seems optimal

//reserved outside and cleared 0.0900s!

//record holder 5/24/2016 0.100s
const int BASE = (1<<5)-1;
unordered_map<long long,int>myMap;
const int MAX_STRING_SIZE = 1000010;
int main() {
	ios_base::sync_with_stdio(false);
	int passwordLength; 
	vector<long long> power;
	long long value =1;
	for(int i=0;i<=10;i++) {
		power.push_back(value);
		value*=BASE;
	}
	myMap.reserve(MAX_STRING_SIZE);

	int r = fread(buff,1,sizeof(buff), stdin);
	//if (r == sizeof(buff)) {printf("done\n"); return 0;}
	//if (r < sizeof(buff)) {printf("done\n"); return 0;}
	if (r == sizeof(buff)) throw -1;
	//printf ("r = %d\n", r);
	int buffPlace = 0;
	
	while (true) {

		//get number 
		passwordLength = 0;

		while (buffPlace< r && buff[buffPlace] <= 32)buffPlace++;
		if (buffPlace>=r) break;
		while (buff[buffPlace] >='0') {
			//printf("in %d\n", passwordLength);
			passwordLength*=10;
			//printf("character working on %c\n", buff[buffPlace]);
			passwordLength += buff[buffPlace++]-'0';
		} 
		//printf("passwordLength = %d\n", passwordLength);
		while (buff[buffPlace] <= 32)buffPlace++;
		//if (s.size() > MAX_STRING_SIZE) throw -1;
		myMap.clear();

		int curMax  = 0;
		int ansPlace = 0;
		//buld string (assuming passowdlengh < s.leng)
		char *s = buff+buffPlace;
		long long hash = 0;
		for(int i=0;i<passwordLength;i++) {
			hash = hash*BASE + s[i]-'a'+1;

			//printf("character working S on %c\n", s[i]);
		}

		myMap[hash]++;
		curMax = 1;

		//cerr << "hash " << hash << endl;
		//printf ("hash = %d\n", hash);
		buffPlace+=passwordLength;
		int place = 0;
		for(int i=passwordLength; buffPlace<r && s[i]>='a';i++,buffPlace++) {
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
			putchar(s[i]);
		}
		putchar('\n');
		if (buffPlace>=r) break;
		
	}
	return 0;
}