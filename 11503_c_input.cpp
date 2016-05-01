#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <cstdio>
#include <cstring>

//#1 0.030s lucky fucking run
//#2 0.040s readall wth fread only store index of string
//#2 use myhash table/with string/iostream 0.050s
//#2 eliminate map.count() == 0 0.060s
//#3 with FastOoutput 0.090s -> 0.080s
//#3 4/25/2016 0.011s -> 0.090s reserve
//#5 8/12/2015 0.143s

class FastOutput {
	public:
	FastOutput() {
	m_dataOffset = 0;
	}
	~FastOutput() {
		Flush();
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

struct Subset{
	int parent;
	int total;
};

const int MAX_FRIENDS = 100010;
//pair<int,int>adj[MAX_FRIENDS];
Subset subsets[MAX_FRIENDS];

int find(int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets[i].parent);
	return subsets[i].parent;
}

void Union(int x, int y) {
	int xroot = find(x);
	int yroot = find(y);
	
	if (xroot == yroot) return;
	
	if (subsets[xroot].total < subsets[yroot].total) {
		subsets[xroot].parent = yroot;
	} else if (subsets[yroot].total < subsets[xroot].total) {
		subsets[yroot].parent = xroot;
	} else {
		subsets[yroot].parent = xroot;
	}
	int newTotal = subsets[xroot].total + subsets[yroot].total;
	subsets[xroot].total = subsets[yroot].total = newTotal;
}

FastOutput output;
const int FILESIZE_IN_BYTES = 3625000;
const int MAX_STRINGS_IN_FILE = (int)(FILESIZE_IN_BYTES/5.66); // by experiment
const int MAX_STRING_LENGTH = 20;
char buff[FILESIZE_IN_BYTES];

char A[MAX_STRINGS_IN_FILE][MAX_STRING_LENGTH+1];

int arrayIndex;
void readAll() {
	int r = fread(buff, 1, sizeof(buff), stdin);
	arrayIndex  = 0;
	for(int i=0;i<r;++i) {
		int len = 0;
		while (buff[i] >= '0') {
			A[arrayIndex][len++] = buff[i++];
		}
		//#ifdef _WIN32
		if (len)
		//#endif
		    ++arrayIndex;
	}
	arrayIndex = 0;
}

//unordered map 0.076s (0.070) avgs vs 0.056s avg
//#define UNORDERED_MAP
int newIndex = 0;
const int HASH_TABLE_SIZE = 1 << 18;
vector<pair<int,int>> myTable[HASH_TABLE_SIZE]; // index of string, newIndex
vector<int>clearHashes;

int getNewIndex() {
	int hash=0;
	//int len = strlen(s);
	for(int i=0;A[arrayIndex][i];++i) {
		hash = (hash)*31 + A[arrayIndex][i];
		if (hash >= HASH_TABLE_SIZE) hash &= (HASH_TABLE_SIZE-1);
	}

	//find it in the table
	if (myTable[hash].size() == 0) {
		myTable[hash].emplace_back(make_pair(arrayIndex++,newIndex));
		clearHashes.emplace_back(hash);
		return newIndex++;
	} else {
		//check if it's contained
		for(int i=0;i<myTable[hash].size();i++) {
			if (strcmp(A[myTable[hash][i].first],A[arrayIndex])==0) {
				arrayIndex++;
				return myTable[hash][i].second;
			} 
		}
		myTable[hash].emplace_back(make_pair(arrayIndex,newIndex));
		//max bucketsize == 5
		arrayIndex++;
		return newIndex++;
	}
}



int main() {
	readAll();
	//printf ("Done = %s\n", A[arrayIndex+1000]);
	//return 0;
	clearHashes.reserve(MAX_FRIENDS);
	int nCases; 
	sscanf(A[arrayIndex++],"%d",&nCases);

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int length; sscanf(A[arrayIndex++],"%d",&length);
		newIndex = 0;

		for(int i=0;i<length+10;i++) {
			subsets[i].parent=i;
			subsets[i].total=1;
		}
		for(int i=0;i<length;i++) {
			int index1 = getNewIndex();
			int index2 = getNewIndex();
			//printf("%d %d\n",index1, index2);
			
			Union(index1,index2);
			output.PrintUint(subsets[find(index1)].total,'\n');
		}
		#ifndef UNORDERED_MAP
		if (caseNum < nCases) {
			//reset
			for(auto &x:clearHashes) {
				myTable[x].clear();
			}
		}
		#endif
	}
	
	return 0;
}
