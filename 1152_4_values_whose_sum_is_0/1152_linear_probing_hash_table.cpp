#include <bits/stdc++.h>
using namespace std;

//0.430s removal of functions + cheating with no wrapping in buffer
//0.460s linear probing
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

const int NUM_TESTS = 20; // max tests found experimentally
const int lastBit = (1<<30); // 2^29 is largest positive sum
const unsigned MSK = 0x000FFFFF; //0x000FFFFF  2.390 runtime
const int DOUBLE_MAP_SIZE = (MSK)+1;

unsigned hash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}


struct Node {
	int count;
	int value;
};

unsigned clearHashes[SIZE*SIZE];
int clearHashesPlace;

const int HASH_TABLE_SIZE = 64000031;//48000013;//32000011;//16000057
const int MOD = 60000011;
Node hashTable[HASH_TABLE_SIZE];

void insert(int num) {
	
}

int find(int num) {
	
	
}

int arrayLength;
void reset() {
	for(int i=0;i<clearHashesPlace;i++) {
		hashTable[clearHashes[i]].count = 0;
	}
}

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
		clearHashesPlace = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				int num = A[i] + B[j];
				unsigned hashIndex = unsigned(num) % MOD;

				//do linear probing
				if (hashTable[hashIndex].count == 0) {
					hashTable[hashIndex].count = 1;
					hashTable[hashIndex].value = num;
					clearHashes[clearHashesPlace++] = hashIndex;
				} else {
					if (hashTable[hashIndex].value == num) {
						hashTable[hashIndex].count++;
					} else {
						//while a value exists and it's not the current one, advance
						++hashIndex;// = (hashIndex + 1) % HASH_TABLE_SIZE;
						while (hashTable[hashIndex].count) {
							if (hashTable[hashIndex].value == num) {
								hashTable[hashIndex].count++;
								goto hell;
							}
							++hashIndex;// = (hashIndex + 1) % HASH_TABLE_SIZE;
						}

						hashTable[hashIndex].count = 1;
						hashTable[hashIndex].value = num;
						clearHashes[clearHashesPlace++] = hashIndex;
					}
				}
				hell:;
			}
		}
		//radix_sort2(sums,sums+sumsPlace, begin1);
		int tot = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				int num = -(C[i]+D[j]);
				//cerr << "num " << num << endl;
				unsigned hashIndex = unsigned(num) % MOD;

				//do linear probing
				if (hashTable[hashIndex].count == 0) continue;
				else {
					if (hashTable[hashIndex].value == num) {
						//cerr << "hashTable " << hashTable[hashIndex].count << endl;
						tot += hashTable[hashIndex].count; continue;
					} else {
						//while a value exists and it's not the current one, advance
						++hashIndex;// = (hashIndex + 1) % HASH_TABLE_SIZE;
						while (hashTable[hashIndex].count) {
							if (hashTable[hashIndex].value == num) {
								tot += hashTable[hashIndex].count;
								//cerr << "hashTable " << hashTable[hashIndex].count << endl;
								goto end;
							}
							++hashIndex;// = (hashIndex + 1) % HASH_TABLE_SIZE;
						}
					}
				}
				end:;
			}
		}
		cout << tot << endl;
		if (caseNum != nCases) {
			reset(); 
			cout << "\n";
		}
	}
	return 0;
}