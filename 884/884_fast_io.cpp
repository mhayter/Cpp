#ifndef __MY_FAST_IO__
#define __MY_FAST_IO__
#include <cstdio>
#include <cstring>
#include <cstdint>

//tied for #1 8/1/2015
//Library stolen from codechef

//outright #1 8/12/2015 0.006s 
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
	uint8_t m_buffer[32768/8];
	uint32_t m_data[16384/8];
	size_t m_dataOffset, m_dataSize;
	uint32_t m_v;
};
#endif
using namespace std;

const int PRIMES_SIZE = 168;
const int primes[PRIMES_SIZE] = {
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 
127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 
179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 
233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 
283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 
353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 
419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 
467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 
547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 
607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 
661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 
739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 
811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 
877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 
947, 953, 967, 971, 977, 983, 991, 997};

const int SIZE = 1000001;
int factorsArray[SIZE+1];
#include <iostream>
#include <bitset>

bitset<SIZE>prime;
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")

void build3() {
	for(int i=2, other=4;other<SIZE;++i,other+=2) {
		prime[other] = 1;
		factorsArray[other] = factorsArray[i] + 1; 
	}
	for(int j=3,other=9;other<SIZE;++j,other+=3) {
		prime[other] = 1;
		factorsArray[other] = factorsArray[j] + 1;
	}
	for(int i=5;i<=997;i+=2) {
		if (!prime[i]) {
			int j=i, other = i*i;
			do {
				factorsArray[other] = factorsArray[j] + 1;
				prime[other] = 1;
				other+=i;
				++j;
			} while (other<SIZE);
			/*for(int j=i, other=i*i;other<SIZE;++j,other+=i) {
				factorsArray[other] = factorsArray[j] + 1;
				prime[other] = 1;
			}
			*/
		}

	}
	for(int i=2;i<SIZE;++i) {
		factorsArray[i] += factorsArray[i-1] + 1;
	} 
}

void build2() {
	//int start = clock();
	for(int j=2,other=4;other<SIZE;++j,other+=2) {
		factorsArray[other] = factorsArray[j] + 1; // 4 1 6 1 8 2 10 1 12 2
	}
	for(int j=3,other=9;other<SIZE;++j,other+=3) {
		factorsArray[other] = factorsArray[j] + 1;
	}
	for (int i=2;i<PRIMES_SIZE;++i) { // slower than sieve ? wtf!!
		int v = primes[i];
		int j = v, other = v*v;
		do {
			factorsArray[other] = factorsArray[j] + 1;
			++j;
			other+=v;
		} while (other < SIZE);
		/*
		for(int j=v,other=v*v;other<SIZE;++j,other+=v) { // v^2 - size v  1 - size
			factorsArray[other] = factorsArray[j] + 1;
		}*/
	}
	for(int i=2;i<SIZE;++i) {
		factorsArray[i] += factorsArray[i-1] + 1;
	} 
}
#pragma GCC pop_options
/*void build() {
	for(int i=2;i<SIZE;i++) {
		int num = i;
		int nFactors = 0;
		while (num && num % 2 == 0) {
			num/=2;
			++nFactors;
		}
		int divisor = 3;
		int intSqrt = sqrt(i) + 1;
		while (num && divisor<= intSqrt) {
			if (num % divisor == 0) {
				num/=divisor;
				++nFactors;
			} else {
				divisor+=2;
			}
		}

		if (num>=2) ++nFactors;

		factorsArray[i] = factorsArray[i-1] + nFactors;
	}
}
*/
#include <iostream>
//FastInput input;
uint8_t m_data[8*32768];
size_t m_dataOffset;
/*
namespace CodeForcesIO {
static char stdinBuffer[32*1024];
static char* stdinDataEnd = stdinBuffer + sizeof (stdinBuffer);
static const char* stdinPos = stdinDataEnd;
static bool eof = false;

void readAhead(size_t amount)
{
	int remaining = stdinDataEnd - stdinPos;
    if (remaining < amount) {
       memmove(stdinBuffer, stdinPos, remaining);
       size_t sz = fread(stdinBuffer + remaining, 1, sizeof (stdinBuffer) - remaining, stdin);
       stdinPos = stdinBuffer;
       stdinDataEnd = stdinBuffer + remaining + sz; 
       if (sz + remaining <  sizeof (stdinBuffer)) eof = true;
    }
}

int readInt()
{
    if (!eof) readAhead(16);
    while (*stdinPos < '0') ++stdinPos;
    if (stdinPos >= stdinDataEnd) return 0x80000000;
    int x = 0;
    while (*stdinPos >= '0') {
       x = x * 10 + *stdinPos - '0';
       ++stdinPos;
    }

    return x;
}
}
*/
#include <ctime>
FastInput input;
int main() {
	int start = clock();
	build2();//takes 0.03s (the whole time)
	cerr << clock() - start << endl;
	//cout <<"f bitches" << endl;
	int n;
	//diff between this iand cin is 0.03s
	while ((n = input.readNextUnsigned()) != 0x80000000) {
		//cerr << "n = " << n << endl;
		if (m_dataOffset + 11 > sizeof(m_data)) {
			fwrite(m_data,1, m_dataOffset,stdout);
			m_dataOffset = 0;
		}
		int v = factorsArray[n];
		if (v < 100000) {
			if (v < 1000) {
				if (v >= 100) { //3
					m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 0] = v + 48;
					m_dataOffset += 3;
				} else if (v < 10) { // 4
					m_data[m_dataOffset + 0] = v + 48;
					m_dataOffset += 1;
				} else { //4
					m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 0] = v + 48;
					m_dataOffset += 2;
				}
			} else {
				if (v < 10000) { // 3
					m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 0] = v + 48;
					m_dataOffset += 4;
				} else { // 3
					m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
					m_data[m_dataOffset + 0] = v + 48;
					m_dataOffset += 5;
				}
			}
		} else {
			if (v < 1000000) { // 2
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 6;
			} else { // 2
				m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
				m_data[m_dataOffset + 0] = v + 48;
				m_dataOffset += 7;
			} 
		}
		m_data[m_dataOffset++] = '\n';
	}
	//output.flush();
	if (m_dataOffset) {
		fwrite(m_data,1, m_dataOffset,stdout);
		m_dataOffset = 0;
	}
	return 0;
}