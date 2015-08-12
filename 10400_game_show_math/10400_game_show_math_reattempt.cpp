//#include "my_fast_io.h"
#include <cstdio>
#include <iostream>
#include <bitset>

#ifndef __MY_FAST_IO__
#define __MY_FAST_IO__
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

void PrintStr(const char *str) {
	if (strlen(str) + m_dataOffset > sizeof(m_data)) Flush();
	while (m_data[m_dataOffset++] = *str++);
}
public:
	uint8_t m_data[32768];
	size_t m_dataOffset;
}; 
#endif

/*
namespace FastIO {
	#define X10(n)	((n << 3) + (n << 1))
	#define RI		readint
	const int MAXR = 65536/2;
	char buf[MAXR], *lim = buf + MAXR - 1, *now = lim + 1;
	int memo[MAXR/2]; int *mPtrEnd = memo; int *mPtrPlace = memo;
	int r;
	int val;
	int readint(){ // Returns true on success, false on failure
		if(mPtrPlace == mPtrEnd){ // memo is filled up
			r = fread(buf, 1, MAXR, stdin);
			//buf[r] = 0;
			lim = buf + r - 1;
			if(r == MAXR){ //read everything (input is large)
				while(*lim >= '0') ungetc(*lim--, stdin);
				if(*lim == '-') ungetc(*lim--, stdin);
			}
			now = buf;
			mPtrPlace = memo;
			mPtrEnd = memo;
			
			while (now <= lim) {
				while( *now < '0' && now <= lim) ++now;
				val = 0;
				bool in = (*now >='0' && now <= lim);
				bool neg = in && (*(now-1)=='-');
				while (*now >='0' && now <= lim) {
					val = X10(val) + *now++ - '0';
				}
				if (in) {
					if (neg) val*=-1;
					*mPtrEnd++ = val;
					//rr << "val = " << val <<"  now " << (int)(now - buf) << " lim " <<(int)(lim-buf)<< endl; 
				}
			}
			//if (mPtrPlace !=  mPtrEnd) n = *mPtrPlace++;
		}
		return *mPtrPlace++;
	}
}
*/
using namespace std;

char ops[]="+-*/";
int operands[110];
char operators[110];
int nNums;
bool solFound;
int ans;

const int ADD = 32000;

bitset<64010> memo[110];

void findSol(int depth,int val) {
	//if (val > ADD*5 ||  val < -ADD*5) return;
	if (depth == nNums) {
		if (val == ans) {
			for(int i=0;i+1<nNums;++i) {
				printf("%d%c",operands[i],operators[i+1]);
			}
			printf("%d", operands[nNums-1]);
			printf("=%d\n", ans);
			solFound = true;
		}
		return;
	}

	if (val <=ADD && val>=-ADD) {
		if (memo[depth][val+ADD]) return;
		memo[depth][val+ADD] = 1;
	} else {
		return;
	}
	//add
	operators[depth] = '+';
	findSol(depth+1,val+operands[depth]);
	if (solFound) return;

	operators[depth] = '-';
	findSol(depth+1,val-operands[depth]);
	if (solFound) return;

	operators[depth] = '*';
	findSol(depth+1,val*operands[depth]);
	if (solFound) return;

	if (val % operands[depth] ==0 ) {
		operators[depth] = '/';
		findSol(depth+1,val/operands[depth]);
		if (solFound) return; // needed?
	}
}

int main() {
	//FastInput input;
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	for(int caseNum=1;caseNum<=n;++caseNum) {

		cin >> nNums ;
		for(int i=0;i<nNums;++i) {
			cin >> operands[i];
			//cerr << "ops " << operands[i] << " ";
			memo[i] = 0;
		}
		//cerr << endl;
		cin >> ans;
		solFound = false;
		findSol(1,operands[0]);
		if (!solFound) {
			puts("NO EXPRESSION");
		}
	}
	return 0;
}