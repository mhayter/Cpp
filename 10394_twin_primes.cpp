#include <iostream>
#include <vector>
#include <bitset>
using namespace std;


#include <cstring>
#include <cstdio>
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

vector<pair<int,int>>twin;
const int SIZE = 20000000;
bitset<SIZE+10> primes;

void sieve() {
	for(int i=2; i*i<=SIZE;i++) {
		if (!primes[i])
		for (int j=i*i;j<=SIZE;j+=i) {
			primes[j]=1;
		}
	}
	for(int i=3;i+2<=SIZE;i+=2) {
		if (!primes[i] && !primes[i+2]) {
			twin.push_back(make_pair(i,i+2));
		}
	}
}

int main() {
	int n; 
	FastInput input;
	sieve();
	//ios_base::sync_with_stdio(false);
	//printf("hey\n");
	while (true) {
		n = input.ReadNext();
		//printf("%d\n", n);
		if (n==0x80000000) break;
		printf("(%d, %d)\n", twin[n-1].first, twin[n-1].second);
		//cout << "(" << twin[n-1].first << ", " << twin[n-1].second << ")\n";
	}
	return 0;
}