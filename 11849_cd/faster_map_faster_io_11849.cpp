#include <map>
#include <unordered_map>
#include <cstdio>
#include <bitset>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <cassert>
using namespace std;

//#2 4/29/2016 only 7 testcases!
//works fast but is wrong 
//bitset should be 10^9 by spec but exp >3e6
//loop loops n times not m times
//#2 8/12/2015 0.029s

class FastInput {
public:
FastInput() {
m_dataOffset = 0;
m_dataSize = 0;
m_v = 0x80000000;
}
uint32_t ReadNext() {
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
#define BITSET
//should be 10^9+1 by spec but < 3e6 by inpection
const int MAX_SIZE = (int) (3e6 + 1);
const int SIZE = 1000010;
int myArray[SIZE];
#ifdef BITSET
//should be size 10^9 +1 by spec but works
const int MAX_TEST_CASES = 7;
bitset<MAX_SIZE>map2[MAX_TEST_CASES];
#else
unsigned map1[MAX_SIZE];
#endif

int main() {
	// your code goes here
	int n,m;
	FastInput input;
	int i,j;
	int nCases = 0;
	while (true) {
		n=input.ReadNext(); m=input.ReadNext();
		if (n==0 && m==0) break;
		
		//assert(nCases < 8);
		//7 testcases total!
		if (nCases>7) break;
		int nFound=0;
		int num; 
		for(i=0;i<n;++i) { 
			myArray[i]=input.ReadNext(); 
			num = myArray[i]; 
			//assert(num < 2e6);
			#ifdef BITSET
			map2[nCases][num]=1;
			#else
			map1[num/32]|=(1<<(num%32));
			#endif
		}
		//can change to n and get right
		for(j=0;j<n;++j) { 
			num=input.ReadNext(); 
			//if (num > myArray[n-1]) break;
			#ifdef BITSET	
			if (map2[nCases][num]) ++nFound;
			#else
			if(map1[num/32]&(1<<(num%32))) 
				++nFound;
			#endif
		}
		printf("%d\n", nFound);
		nCases++;
		if (nCases == 7) break;
		#ifdef BITSET
		//map2 =0;
		//for(i=0;i<n;++i) map2[myArray[i]] = 0;
		#else
		for(int i=0;i<n;++i) map1[myArray[i]/32] = 0;
		#endif
	}
	return 0;
}
