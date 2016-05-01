#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

//generate carmichael nums to file; 
//hardcode values in map; use fast input (apparently super big input)
//tied #1

int modpow(long long base, long long exp, long long modulus) {
  base %= modulus;
  long long  result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

bool passesFermat(int n) {
	//b^(n-1) == 1 (mod n) | n is the prime
	for(int b=2;b<n;b++)
		if (gcd(n,b) == 1)
			if (modpow(b,n-1,n) != 1) return false;
	return true;
}

vector<int>carmichaelNumbers;

const int MAX_NUM = 65000;
bitset<MAX_NUM+10> isPrime;

void generatePrimes() {
	isPrime.set();
	int limit = sqrt(MAX_NUM) + 1;
	for(int i=2;i<=limit;i++) {
		if (isPrime[i]) {
			for(int j=i*i; j<MAX_NUM;j+=i) {
				isPrime[j] = 0;
			}
		} 
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
        uint8_t m_buffer[32768*2];
        uint32_t m_data[16384*2];
        size_t m_dataOffset, m_dataSize;
        uint32_t m_v;
};


int main() {
	FastInput input;
	//ios_base::sync_with_stdio(false);
	/*
	generatePrimes();
	//cout << 1729 << " " << !isPrime[1729] << " " << passesFermat(1729) << endl;
	for(int i=3;i<MAX_NUM;i+=2) {
		//cout << "PRocessing " << i << "\n";
		if (!isPrime[i] && passesFermat(i)) {
			carmichaelNumbers.push_back(i);
		}
	}
	for(auto &x:carmichaelNumbers) {
		cout << x << ", ";
	}
	cout << endl;
	*/
	//cerr << "done\n";
	unordered_set<int> isCarmichael{561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973};
	int num = input.readNextUnsigned(); 
	while (true) {
		if (num == 0) break;
		if (isCarmichael.find(num) != isCarmichael.end()) {
			cout << "The number " << num << " is a Carmichael number.\n";
		} else {
			cout << num << " is normal.\n";
		}
		num = input.readNextUnsigned();
	}
	return 0;
}