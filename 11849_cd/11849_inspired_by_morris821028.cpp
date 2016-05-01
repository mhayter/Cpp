#include <map>
#include <unordered_map>
#include <cstdio>
#include <bitset>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
using namespace std;

//use sorted order exploit
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
class FastOutput {
public:
FastOutput() {
m_dataOffset = 0;
}
~FastOutput() {
}
void Flush() {
if (m_dataOffset) {
if (fwrite(m_data,1, m_dataOffset,stdout));
m_dataOffset = 0;
}
}
void PrintUint(uint32_t v, char d) {
if (m_dataOffset + 11 > sizeof(m_data)) Flush();
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
void PrintChar(char d) {
if (m_dataOffset + 1 > sizeof(m_data)) Flush();
m_data[m_dataOffset++] = d;
}
void ReplaceChar(int offset, char d) {
m_data[m_dataOffset + offset] = d;
}
public:
uint8_t m_data[32768];
size_t m_dataOffset;
}; 
const int MAX_SIZE = 1000000000/32 + 1;
const int SIZE = 1000010;
int myArray[SIZE];


int main() {
	// your code goes here
	int n,m;
	FastInput input;
	FastOutput output;
	int i,j;
	int nCases = 0;
	while (true) {
		n=input.ReadNext(); m=input.ReadNext();
		if (n==0 && m==0) break;
		nCases++;
		if (nCases>32) break;
		int nFound=0;
		int num; 
		for(i=0;i<n;++i) { 
			myArray[i]=input.ReadNext(); 
		}
		//can change to n and get right
		int index = 0;
		for(j=0;j<m;++j) { 
			num=input.ReadNext(); 
			while (index < n) {
				if (myArray[index] == num) {
					++nFound;
					++index;
				} else if (myArray[index] < num) {
					++index;
				} else {
					//index = n;
					break; // over limit 
				}
			}
		}
		output.PrintUint(nFound,'\n');
	}
	output.Flush();
	return 0;
}
