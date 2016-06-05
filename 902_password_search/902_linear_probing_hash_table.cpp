//#include <iostream>
//#include <string>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdint>
using namespace std;

//new fastest 0.060s linear probing hashtable mod 32000011 with 1010*1000 unique hashes!

namespace HashTable {

	struct Node {
		int count;
		uint64_t value;
	};
	const int MOST_UNIQUE_HASHES = 1010*1000;
	unsigned clearHashes[MOST_UNIQUE_HASHES];
	int clearHashesPlace = 0;

	const int HASH_TABLE_SIZE = 32000011;//64000031;//48000013;//;//16000057
	Node hashTable[HASH_TABLE_SIZE];

	int insert(uint64_t num) {
		uint64_t hashIndex = num % HASH_TABLE_SIZE;

		//do linear probing
		if (hashTable[hashIndex].count == 0) {
			hashTable[hashIndex].value = num;
			//cerr << "New Element " << num  << " " << hashTable[hashIndex].count << endl;
			clearHashes[clearHashesPlace++] = hashIndex;
			return hashTable[hashIndex].count = 1;
		} else {
			if (hashTable[hashIndex].value == num) {
				return ++hashTable[hashIndex].count;
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) {
						return ++hashTable[hashIndex].count;
					}
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}

				
				hashTable[hashIndex].value = num;
				clearHashes[clearHashesPlace++] = hashIndex;
				return hashTable[hashIndex].count = 1;
			}
		}
	}

	int find(uint64_t num) {
		uint64_t hashIndex = num % HASH_TABLE_SIZE;

		//do linear probing
		if (hashTable[hashIndex].count == 0) return 0;
		else {
			if (hashTable[hashIndex].value == num) {
				return hashTable[hashIndex].count;
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) return hashTable[hashIndex].count;
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}
				return 0;
			}
		}
		
	}

	void clear () {
		for(int i=0;i<clearHashesPlace;i++) {
			hashTable[clearHashes[i]].count = 0;
		}
		clearHashesPlace = 0;
	}
};

const int MAX_CHARACTERS_IN_FILE = 10000010;
char buff[MAX_CHARACTERS_IN_FILE];
const int BASE = (1<<5)-1;

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

	int r = fread(buff,1,sizeof(buff), stdin);
	int buffPlace = 0;
	
	while (true) {
		passwordLength = 0;

		while (buffPlace< r && buff[buffPlace] <= 32)buffPlace++;
		if (buffPlace>=r) break;
		while (buff[buffPlace] >='0') {
			passwordLength*=10;
			passwordLength += buff[buffPlace++]-'0';
		} 
		while (buff[buffPlace] <= 32)buffPlace++;
		HashTable::clear();

		int curMax  = 0;
		int ansPlace = 0;
		//buld string (assuming passowdlengh < s.leng)
		char *s = buff+buffPlace;
		uint64_t hash = 0;
		for(int i=0;i<passwordLength;i++) {
			hash = hash*BASE + s[i]-'a'+1;
		}
		HashTable::insert(hash);
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
			int num = HashTable::insert(hash);
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