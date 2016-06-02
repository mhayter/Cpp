#include <bits/stdc++.h>
using namespace std;

//2.760s no clear for testCases;
//2.430s % big prime
//6.230s double map
//2.370s htable with vector
//2.320s radix_sort + negative bit transformation up - low
//2.670s conditonal early exit up - low
//2.650s std::sort + upper_bound - lower_bound

//3.950s remove if statement 
//3.380s reserve map
//5.02s -> 4.820s  int works despite wrong


namespace CodeForcesIO {
	static char stdinBuffer[1024];
	static char* stdinDataEnd = stdinBuffer + sizeof (stdinBuffer);
	static const char* stdinPos = stdinDataEnd;

	void readAhead(size_t amount)
	{
	    size_t remaining = stdinDataEnd - stdinPos;
	    if (remaining < amount) {
	       memmove(stdinBuffer, stdinPos, remaining);
	       size_t sz = fread(stdinBuffer + remaining, 1, sizeof (stdinBuffer) - remaining, stdin);
	       stdinPos = stdinBuffer;
	       stdinDataEnd = stdinBuffer + remaining + sz;
	       if (stdinDataEnd != stdinBuffer + sizeof (stdinBuffer))
	         *stdinDataEnd = 0;
	    }
	}

	int readInt()
	{
	    readAhead(16);

	    int x = 0;
	    bool neg = false;
	    while (*stdinPos <'-') ++stdinPos;

	    if (*stdinPos == '-') {
	       ++stdinPos;
	       neg = true;
	    }

	    while (*stdinPos >= '0' && *stdinPos <= '9') {
	       x *= 10;
	       x += *stdinPos - '0';
	       ++stdinPos;
	    }


	    return neg ? -x : x;
	}
}

const int SIZE = 4010;
int A[SIZE];
int B[SIZE];
int C[SIZE];
int D[SIZE];



//unsigned sums[SIZE*SIZE];
const int NUM_TESTS = 20; // max tests found experimentally
const int lastBit = (1<<30); // 2^29 is largest positive sum
const unsigned MSK = 0x000FFFFF; //0x000FFFFF  2.390 runtime
const int DOUBLE_MAP_SIZE = (MSK)+1;


const int BIG_PRIME_GREATER_THAN_ONE_MILLION = 1000003; // //16000057

vector<pair<unsigned,unsigned>> table[NUM_TESTS][BIG_PRIME_GREATER_THAN_ONE_MILLION];

unsigned hash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

int arrayLength;

int main() {
	ios_base::sync_with_stdio(false);
	int nCases = CodeForcesIO::readInt();

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		arrayLength = CodeForcesIO::readInt();
		for(int i=0;i<arrayLength;i++) {
			A[i] = CodeForcesIO::readInt();
			B[i] = CodeForcesIO::readInt();
			C[i] = CodeForcesIO::readInt();
			D[i] = CodeForcesIO::readInt();
		}
		//ABSum[caseNum].reserve(arrayLength*arrayLength);
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				unsigned sum = (unsigned) (A[i]+B[j]);
				unsigned msk = sum % BIG_PRIME_GREATER_THAN_ONE_MILLION;
				
				bool found = false;
				for(int i=0;i<table[caseNum][msk].size();i++) {
					if (table[caseNum][msk][i].first == sum) {
						table[caseNum][msk][i].second++;
						found = true;
						break;
					}
				}
				if (!found){
					table[caseNum][msk].emplace_back(make_pair(sum,1));
				} 
			}
		}
		int tot = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				unsigned sum = (unsigned)(-(C[i] + D[j]));
				unsigned msk = sum % BIG_PRIME_GREATER_THAN_ONE_MILLION;
				for(int i=0;i<table[caseNum][msk].size();i++) {
					if (table[caseNum][msk][i].first == sum) {
						tot+=table[caseNum][msk][i].second;
						break;
					}
				}
			}
		}
		cout << tot << "\n";
		if (caseNum != nCases) {
			cout << "\n";
		}
	}
	return 0;
}