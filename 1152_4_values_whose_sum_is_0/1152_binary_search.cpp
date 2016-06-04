#include <bits/stdc++.h>
using namespace std;


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

void _radix_sort_lsb(unsigned *begin, unsigned *end, unsigned *begin1, unsigned maxshift){
    unsigned *end1 = begin1 + (end - begin);
 
    for (unsigned shift = 0; shift <= maxshift; shift += 8)
    {
        size_t count[0x100] = {};
        for (unsigned *p = begin; p != end; p++)
            count[(*p >> shift) & 0xFF]++;
        unsigned *bucket[0x100], *q = begin1;
        for (int i = 0; i < 0x100; q += count[i++])
            bucket[i] = q;
        for (unsigned *p = begin; p != end; p++)
            *bucket[(*p >> shift) & 0xFF]++ = *p;
        std::swap(begin, begin1);
        std::swap(end, end1);
    }
}

void _radix_sort_msb(unsigned *begin, unsigned *end, unsigned *begin1, unsigned shift)
{
    unsigned *end1 = begin1 + (end - begin);
 
    size_t count[0x100] = {};
    for (unsigned *p = begin; p != end; p++)
        count[(*p >> shift) & 0xFF]++;
    unsigned *bucket[0x100], *obucket[0x100], *q = begin1;
    for (int i = 0; i < 0x100; q += count[i++])
        obucket[i] = bucket[i] = q;
    for (unsigned *p = begin; p != end; p++)
        *bucket[(*p >> shift) & 0xFF]++ = *p;
    for (int i = 0; i < 0x100; ++i)
        _radix_sort_lsb(obucket[i], bucket[i], begin + (obucket[i] - begin1), shift - 8);
}

void radix_sort2(unsigned *begin, unsigned *end, unsigned *begin1){
    _radix_sort_msb(begin, end, begin1, 24);
}

const int SIZE = 4010;
int A[SIZE];
int B[SIZE];
int C[SIZE];
int D[SIZE];



//unsigned sums[SIZE*SIZE];
const int NUM_TESTS = 20; // max tests found experimentally
unordered_map<int,int> ABSum[NUM_TESTS];





const int lastBit = (1<<30); // 2^29 is largest positive sum

//unsigned begin1[SIZE*SIZE];
const unsigned MSK = 0x000FFFFF; //0x000FFFFF  2.390 runtime
const int DOUBLE_MAP_SIZE = (MSK)+1;
//unordered_map<unsigned,unsigned> doubleMap[DOUBLE_MAP_SIZE];

vector<pair<unsigned,unsigned>> table[DOUBLE_MAP_SIZE];

unsigned hash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

unsigned clearHashes[SIZE*SIZE];
int clearHashesPlace;

int arrayLength;
void reset() {
	for(int i=0;i<clearHashesPlace;i++) {
		table[clearHashes[i]].clear();
		//doubleMap[clearHashes[i]].clear();
	}
}

int main() {
	//clearHashes.reserve(SIZE*SIZE);
	ios_base::sync_with_stdio(false);
	int nCases = CodeForcesIO::readInt();
	//if (nCases > 10) throw -1;

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		arrayLength = CodeForcesIO::readInt();
		for(int i=0;i<arrayLength;i++) {
			A[i] = CodeForcesIO::readInt();
			B[i] = CodeForcesIO::readInt();
			C[i] = CodeForcesIO::readInt();
			D[i] = CodeForcesIO::readInt();
		}
		//ABSum[caseNum].reserve(arrayLength*arrayLength);
		clearHashesPlace = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				/*int sum = A[i]+B[j];
				if (sum < 0){
					sum = -sum;
					sum |= lastBit;
				}
				*/
				unsigned sum = (unsigned) (A[i]+B[j]);


				//ABSum[caseNum][sum]++;
				
				unsigned msk = sum & MSK;
				
				bool found = false;
				for(int i=0;i<table[msk].size();i++) {
					if (table[msk][i].first == sum) {
						table[msk][i].second++;
						found = true;
						break;
					}
				}
				if (!found){
					clearHashes[clearHashesPlace++] = msk;
					table[msk].emplace_back(make_pair(sum,1));
				} 
				/*
				int num = ++doubleMap[msk][sum];
				if (num == 1) {
					clearHashes[clearHashesPlace++] = msk;
				}
				*/
				//sums[sumsPlace++] = (unsigned) (A[i]+B[j]);
			}
		}
		//radix_sort2(sums,sums+sumsPlace, begin1);
		int tot = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				unsigned sum = (unsigned)(-(C[i] + D[j]));
				/*auto it = ABSum[caseNum].find(sum);
				if (it != ABSum[caseNum].end())
					tot += it->second;
				if (sum < 0){
					sum = -sum;
					sum |= lastBit;
				}
				*/
				unsigned msk = sum & MSK;
				for(int i=0;i<table[msk].size();i++) {
					if (table[msk][i].first == sum) {
						tot+=table[msk][i].second;
						break;
					}
				}
				/*
				auto it = doubleMap[msk].find(sum);
				if (it != doubleMap[msk].end())
					tot += it->second;
				*/
				//tot += upper_bound(sums,sums+sumsPlace, sum) - lower_bound(sums,sums+sumsPlace, sum);
				//cerr << "sum " << sum << " tot " << tot << endl;
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