#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int SIZE = 100000;
int happy [SIZE];

int isHappy[9*9*5+10];
const int INF = 1000000000;

int getSum(int num) {
	int sum  = 0;
	while (num) {
		int digit = num % 10;
		sum += digit*digit;
		num /= 10;
	}
	return sum;
}


void getHappy() {
	for(int i=1;i<500;i++) {
		unordered_set<int> mySet;
		//cerr << "Processing " << i << endl;
		int num = i;
		int len = 0;
		int sum = 0;
		mySet.insert(num);
		bool isSet = false;
		while (num != 1) {
			num = getSum(num);
			//cerr << "num " << num << endl;
			len++;
			if (mySet.count(num) ) {
				//cerr << "break it" << endl;
				for(auto &x:mySet) {
					isHappy[x] = INF;
				}
				break;
			}
			mySet.insert(num);
			if (isHappy[num]) {
				if (isHappy[num] != INF) {
					happy[i] = len + isHappy[num]; 
				} 
				isSet = true;
				break;
			}
			
			
		}
		//cerr << "out " << endl;
		
		if (num == 1) {
			happy[i] = len+1;
		} 
		//cerr << "yes" << endl;

	}
}


#include <cstdio>
#include <cstring>
#include <cstdint>
//Library stolen from codechef
class FastInput {
public:
FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
}
uint32_t readNextUnsigned() {
	if (m_dataOffset == m_dataSize) {
		int r = fread(m_buffer,1,sizeof(m_buffer),stdin);
		if (r <= 0) return m_v;
		m_dataOffset = 0;
		m_dataSize = 0;
		int i = 0;
		if (m_buffer[0] < '0') {
			if (m_v != 0x80000000) {
				m_data[m_dataSize++] = m_v;
				m_v = 0x80000000;
			}
			for (; (i < r) && (m_buffer[i] < '0'); ++i);
		}
		for (; i < r;) {
			if (m_buffer[i] >= '0') {
				m_v = m_v * 10 + m_buffer[i] - 48;
				++i;
			} else {
				m_data[m_dataSize++] = m_v;
				m_v = 0x80000000;
				for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
			}
		}
	}
	return m_data[m_dataOffset++];
}
public:
	uint8_t m_buffer[32768];
	uint32_t m_data[16384];
	size_t m_dataOffset, m_dataSize;
	uint32_t m_v;
};

class FastOutput {
public:
FastOutput() {
	m_dataOffset = 0;
}
~FastOutput() {
	flush();
}
void flush() {
	if (m_dataOffset) {
		if (fwrite(m_data,1, m_dataOffset,stdout));
		m_dataOffset = 0;
	}
}

void printUnsigned(uint32_t v, char d) {
	if (m_dataOffset + 11 > sizeof(m_data)) flush();
	if (v < 100000) {
		if (v < 1000) {
			if (v < 10) {
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 1;
			} else if (v < 100) {
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 2;
			} else {
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 3;
			}
		} else {
			if (v < 10000) {
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 4;
			} else {
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 5;
			}
		}
	} else {
		if (v < 100000000) {
			if (v < 1000000) {
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 6;
			} else if (v < 10000000) {
				m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 7;
			} else {
				m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 8;
			}
		} else {
			if (v < 1000000000) {
				m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 9;
			} else {
				m_data[m_dataOffset + 9] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 10;
			}
		}
	}
	m_data[m_dataOffset++] = d;
}
void printChar(char d) {
if (m_dataOffset + 1 > sizeof(m_data)) flush();
	m_data[m_dataOffset++] = d;
}
void replaceChar(int offset, char d) {
	m_data[m_dataOffset + offset] = d;
}

void printStr(const char *str) {
	if (strlen(str) + m_dataOffset > sizeof(m_data)) flush();
	while (m_data[m_dataOffset++] = *str++);
}
public:
	uint8_t m_data[32768];
	size_t m_dataOffset;
}; 

int happyList[500];

FastInput input;
FastOutput output;

bool seen[SIZE];
int cnt;

int myMap[SIZE];


int happyNumbers[20000];
int happyNumbersPlace;

int main() {
	ios_base::sync_with_stdio(false);
	getHappy();
	for(int i=1;i<SIZE;i++) {
		int num = getSum(i);
		if (happy[num]) {
			happyNumbers[happyNumbersPlace] = i;
			myMap[i] = happyNumbersPlace;
			happyNumbersPlace++;
		}
	}
	cerr << "happyNumbersPlace " << happyNumbersPlace << endl;
	//cout << happy[100] << "done\n"; return 0;
	int low, high;
	low = input.readNextUnsigned();
	high = input.readNextUnsigned();

	//cin >> low >> high;
	int testNum = 1;
	while (true) {
		//cerr << "low " << low << " high " << high << endl;
		if (low == 1) {  
			output.printUnsigned(1, ' ');
			output.printUnsigned(1, '\n');
			int place = 1;
			while (place < happyNumbersPlace && happyNumbers[place] <=high) {
				output.printUnsigned(happyNumbers[place], ' ');
				int num = getSum(happyNumbers[place]);
				output.printUnsigned(happy[num]+1, '\n');
				place++;
			}
			//cout << "1 1\n"; 
			/*for(int i=low+1;i<=high;i++) {
				if (seen[i]) cnt++;
				seen[i] = true;
				int sum  = 0;
				int num = i;
				while (num) {
					int digit = num % 10;
					sum += digit*digit;
					num /= 10;
				}
				if (happy[sum]) {
					output.printUnsigned(i, ' ');
					output.printUnsigned(happy[sum]+1, '\n');
					//cout << i << " " << happy[num] + 1 << "\n";
				}
			}
			*/
		} else {
			int place = std::lower_bound(happyNumbers, happyNumbers+happyNumbersPlace,low) - happyNumbers;
			while (place < happyNumbersPlace && happyNumbers[place] <=high) {
				output.printUnsigned(happyNumbers[place], ' ');
				int num = getSum(happyNumbers[place]);
				output.printUnsigned(happy[num]+1, '\n');
				place++;
			}
			/*
			for(int i=low;i<=high;i++) {
				if (seen[i]) cnt++;
				seen[i] = true;

				int sum  = 0;
				int num = i;
				while (num) {
					int digit = num % 10;
					sum += digit*digit;
					num /= 10;
				}
				if (happy[sum]) {
					output.printUnsigned(i, ' ');
					output.printUnsigned(happy[sum]+1, '\n');
					//cout << i << " " << happy[num] + 1 << "\n";
				}
			}
			*/
		}
		testNum++;
		//if (testNum > 50) throw -1; 50 < tests < 100
		//cerr << "test " <<testNum++ << endl; 
		low = input.readNextUnsigned();
		if (low == 0x80000000) break;
		else output.printChar('\n');
		high = input.readNextUnsigned();

	}
	if (cnt > 2200000) {
		cerr << "throwing " << endl;
		throw -1;
	}
	return 0;
}
