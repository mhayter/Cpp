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

//slower than using the s off in 902_faster_input ?

const int BASE = (1<<5)-1;
unordered_map<long long,int>myMap;
const int MAX_STRING_SIZE = 1000010;
int main() {
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

		while (buffPlace< r && buff[buffPlace] <= 32) buffPlace++;
		if (buffPlace>=r) break;
		while (buff[buffPlace] >='0') {
			passwordLength*=10;
			passwordLength += buff[buffPlace++]-'0';
		} 
		while (buff[buffPlace] <= 32)buffPlace++;
		myMap.clear();

		int curMax  = 0;
		int ansPlace = buffPlace;
		//buld string (assuming passowdlengh < s.leng)
		long long hash = 0;
		for(int i=0;i<passwordLength;i++) {
			hash = hash*BASE + buff[buffPlace++]-'a'+1;
		}
		//printf("hash %d\n", hash);
		myMap[hash]++;
		curMax = 1;

		int place = 0;
		for(; buffPlace<r && buff[buffPlace]>='a';buffPlace++) {
			//printf("Char %c\n", buff[buffPlace]);
			//printf("Target char %c\n", buff[buffPlace- passwordLength]);
			hash -= power[passwordLength-1]*(buff[buffPlace- passwordLength]-'a'+1);
			hash *= BASE;
			hash += buff[buffPlace]-'a'+1; 

			int num = ++myMap[hash];
			if (num > curMax) {
				curMax = num;
				ansPlace = buffPlace - passwordLength+1;
				//printf("ansPlace = %d char is %c\n", ansPlace, buff[ansPlace]);
			}
		}
		for(int i=ansPlace, nTimes=0;nTimes<passwordLength;i++,nTimes++){
			putchar(buff[i]);
		}
		putchar('\n');
		if (buffPlace>=r) break;
		//break;
	}
	return 0;
}