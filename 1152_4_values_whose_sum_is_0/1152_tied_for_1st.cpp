#include <bits/stdc++.h>
using namespace std;

//0.450s
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
Node hashTable[HASH_TABLE_SIZE];
int hsize;

void insert(int num) {
	unsigned hashIndex = unsigned(num) % HASH_TABLE_SIZE;

	//do linear probing
	if (hashTable[hashIndex].count == 0) {
		hashTable[hashIndex].count = 1;
		hashTable[hashIndex].value = num;
		//cerr << "New Element " << num  << " " << hashTable[hashIndex].count << endl;
		hsize++;
		clearHashes[clearHashesPlace++] = hashIndex;
	} else {
		if (hashTable[hashIndex].value == num) {
			hashTable[hashIndex].count++;
			//cerr << "Same Element " << num  << " " << hashTable[hashIndex].count << endl;
		} else {
			//while a value exists and it's not the current one, advance
			hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
			while (hashTable[hashIndex].count) {
				if (hashTable[hashIndex].value == num) {
					hashTable[hashIndex].count++;
					return;
				}
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
			}

			hashTable[hashIndex].count = 1;
			hashTable[hashIndex].value = num;
			clearHashes[clearHashesPlace++] = hashIndex;
			//cerr << "New Element " << num  << " " << hashTable[hashIndex].count << endl;
			hsize++;
		}
	}
}

int find(int num) {
	unsigned hashIndex = unsigned(num) % HASH_TABLE_SIZE;

	//do linear probing
	if (hashTable[hashIndex].count == 0) return 0;
	else {
		if (hashTable[hashIndex].value == num) {
			return hashTable[hashIndex].count;
		} else {
			//while a value exists and it's not the current one, advance
			hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
			while (hashTable[hashIndex].count) {
				if (hashTable[hashIndex].value == num) return hashTable[hashIndex].count;
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
			}
			return 0;
		}
	}
	
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
				insert(A[i]+B[j]);
			}
		}
		//radix_sort2(sums,sums+sumsPlace, begin1);
		int tot = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				int sum = C[i]+D[j];
				int nTimes = find(-sum);
				//cerr << "Found " << -sum << " " << nTimes << endl; 
				tot+=nTimes;
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