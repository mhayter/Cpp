//#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <cstdio>
#include <cstring>
// 0.100s scanf
// 0.140s c strings
//#2 eliminate map.count() == 0 0.060s sometimes 0.070s
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


int nItems = 0;
struct Subset{
	Subset() {
		parent = nItems++;
		total = 1;
	}
	int parent;
	int total;
};

const int MAX_FRIENDS = 100010;
//pair<int,int>adj[MAX_FRIENDS];
//Subset subsets[MAX_FRIENDS];
Subset mySubsets[MAX_FRIENDS];

int find(int i) {
	if (mySubsets[i].parent != i)
		mySubsets[i].parent = find(mySubsets[i].parent);
	return mySubsets[i].parent;
}

void Union(int x, int y) {
	int xroot = find(x);
	int yroot = find(y);
	
	if (xroot == yroot) return;
	
	if (mySubsets[xroot].total < mySubsets[yroot].total) {
		mySubsets[xroot].parent = yroot;
	} else if (mySubsets[yroot].total < mySubsets[xroot].total) {
		mySubsets[yroot].parent = xroot;
	} else {
		mySubsets[yroot].parent = xroot;
	}
	int newTotal = mySubsets[xroot].total + mySubsets[yroot].total;
	mySubsets[xroot].total = mySubsets[yroot].total = newTotal;
}

struct myPair {
	myPair(const char *str, int index) {
		this->str = str;
		this->index = index; 
	}
	const char *str;
	int index;
};

const int HASH_TABLE_SIZE = 1 << 18;
vector<myPair> myTable[HASH_TABLE_SIZE];
int newIndex = 0;
vector<int>clearHashes;

int getNewIndex(const char *s) {
	int hash=0;
	//int len = strlen(s);
	for(int i=0;s[i];i++) {
		hash = (hash)*31 + s[i];
		if (hash >= HASH_TABLE_SIZE) hash &= (HASH_TABLE_SIZE-1);
	}

	//find it in the table
	if (myTable[hash].size() == 0) {
		myTable[hash].emplace_back(myPair(s,newIndex));
		clearHashes.emplace_back(hash);
		return newIndex++;
	} else {
		//check if it's contained
		for(int i=0;i<myTable[hash].size();i++) {
			if (strcmp(myTable[hash][i].str,s)==0) {
				return myTable[hash][i].index;
			} 
		}
		myTable[hash].emplace_back(myPair(s,newIndex));
		return newIndex++;
	}
}


int main() {
	clearHashes.reserve(MAX_FRIENDS);
	FastOutput output;
	char line[80];

	int nCases;
	scanf("%d\n", &nCases);
	//gets(line);
	//sscanf(line, "%d\n", &nCases);

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int length; 
		scanf("%d\n", &length);
		//gets(line);
		//sscanf(line, "%d\n", &length);

		newIndex = 0;
		nItems = 0;
		clearHashes.clear();
		//Subset subsets[length+100];//not technically correct?
		//mySubsets = subsets;

		for(int i=0;i<length+100;i++) {
			mySubsets[i].parent=i;
			mySubsets[i].total=1;
		}

		for(int i=0;i<length;i++) {

			char *s1 = new char[21]{'\0'};
			char *s2 = new char[21]{'\0'};


			scanf("%s %s\n", s1,s2);
			//gets(line);
			//sscanf(line, "%s %s\n", s1,s2);

			int index1 = getNewIndex(s1);
			int index2 = getNewIndex(s2);
			
			//printf ("%d %d\n", index1, index2);
			Union(index1,index2);

			output.PrintUint(mySubsets[find(index1)].total,'\n');
		}
		//clear it 
		if (caseNum < nCases) {
			//reset
			for(auto &x:clearHashes) {
				myTable[x].clear();
			}
		}
	}
	return 0;
}
