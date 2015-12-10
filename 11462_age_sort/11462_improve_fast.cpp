#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdint>
using namespace std;

//#5 0.034s (maybe use radix?)
//#1 0.015s 8/12/2015

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
uint8_t m_buffer[32768*2];
uint32_t m_data[16384*2];
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
	if (v < 10) {
		m_data[m_dataOffset + 0] = v + 48;
		m_dataOffset += 1;
	} else { //everybody less than 100
		m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
		m_data[m_dataOffset + 0] = v + 48;
		m_dataOffset += 2;
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

int main() {
	FastInput input;
	//FastOutput output;
	const int O_SIZE = 32768*2;
	uint8_t data[O_SIZE];
	size_t dataOffset = 0;
	int n;
	unsigned smallInput[100];
	while (true) {
		n = input.ReadNext();
		if (n==0) break;
		if (n<32) {
			for(int i=0;i<n;++i) {
				smallInput[i] = input.ReadNext();
			}
			sort(smallInput,smallInput+n);

			//put into output
			for(int i=0;i<n;++i) {
				if (dataOffset + 11 > sizeof(data)) {
					if (dataOffset) {
						fwrite(data,1, dataOffset,stdout);
						dataOffset = 0;
					}
				}
				int v = smallInput[i];
				if (v < 10) {
					data[dataOffset++] = v + 48;
					data[dataOffset++] = ' ';
				} else {
					data[dataOffset++] = v / 10 + 48;
					data[dataOffset++] = v % 10 + 48; 
					data[dataOffset++] = ' ';
				}
			}
			data[dataOffset-1] = '\n';
			continue;
		}
		unsigned a[101]={0};
		for(int i=0;i<n;++i){
			++a[input.ReadNext()];
		}
		for(int i=1;i<=9;++i) {
			for(int j=0;j<a[i];++j){
				if (dataOffset + 11 > sizeof(data)) {
					if (dataOffset) {
						fwrite(data,1, dataOffset,stdout);
						dataOffset = 0;
					}
				}
				data[dataOffset++] = i + 48;
				data[dataOffset++] = ' ';
				--n;
				if (n == 0) goto hell;
			}
		}
		for(int i=10;i<=99;++i) {
			for(int j=0;j<a[i];++j){
				if (dataOffset + 11 > sizeof(data)) {
					if (dataOffset) {
						fwrite(data,1, dataOffset,stdout);
						dataOffset = 0;
					}
				}
				data[dataOffset++] = i / 10 + 48;
				data[dataOffset++] = i % 10 + 48; 
				data[dataOffset++] = ' ';
				--n;
				if (n==0) goto hell;
			}
		}
		hell:;
		//output.m_data[output.m_dataOffset-1] = '\n';
		data[dataOffset-1] = '\n';
	}
	if (dataOffset) {
						fwrite(data,1, dataOffset,stdout);
						dataOffset = 0;
					}
	/*if (dataOffset) {
		fwrite(data,1,dataOffset,stdout);
	}*/
	return 0;
}