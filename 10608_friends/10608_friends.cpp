#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <unordered_set>
using namespace std;


//0.012 (wrong)
//technically wrong given bitset doesn't cover
//unordered set yields 0.014

//#1 tied (2) 0.003s (take out OOP for performance?)

//#define UNION_BY_SIZE
//#define PATH_COMPRESSION

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

class UnionFind{
public:
	struct Subset{
		Subset(){}
		Subset(int a,int b) :
			parent(a), total(b) 
		{}
		int parent;
		int total;
	};
	vector<Subset>subsets;
	int nVerts;
public:
	UnionFind(int nVertices):nVerts(nVertices){
		for(int i=0;i<nVertices;i++) {
			subsets.push_back(Subset(i,1));
		}
	} 
	

int find(int i) {
	/*
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets[i].parent);
	return subsets[i].parent;
	*/
	int x,r;
	r = i;
	while (subsets[r].parent != r) { // find root
		r = subsets[r].parent;
	}
//#ifdef PATH_COMPRESSION
	x = i;
	while (subsets[x].parent != r) {
		int next = subsets[x].parent;
		subsets[x].parent = r;
		x = next;
	}
//#endif
	return r;

/*
	int x = i;
	while (subsets[subsets[x].parent].parent != subsets[x].parent) {
		subsets[x].parent = subsets[subsets[x].parent].parent;
		x = subsets[x].parent;
	}
	return subsets[x].parent;
*/
}

void Union(int x, int y) {
	int xroot = find(x);
	int yroot = find(y);
	
	if (xroot == yroot) return;
///#ifdef UNION_BY_SIZE
	if (subsets[xroot].total < subsets[yroot].total) {
		subsets[xroot].parent = yroot;
	} else if (subsets[yroot].total < subsets[xroot].total) {
		subsets[yroot].parent = xroot;
	} else {
		subsets[yroot].parent = xroot;
	}
//#else
//	subsets[xroot].parent = yroot;
//#endif 
	int newTotal = subsets[xroot].total + subsets[yroot].total;
	subsets[xroot].total = subsets[yroot].total = newTotal;
}
int getTotal(int x) {
	int xroot = find(x);
	return subsets[xroot].total;
}
void fill (int nVertices) {
	for(int i=0;i<nVertices;++i)
		subsets[i] = Subset(i,1);
}
};

const int BASE = 30001;
const int MAX_SIZE = 15384617;

bitset<MAX_SIZE> in;
FastInput input;
//FastOutput output;

int main () {
	ios_base::sync_with_stdio(false);
	
	//cout << "hey" << endl;
	int nCases = input.ReadNext();
	int i,a,b,prod;
	UnionFind uf(BASE);
	for(int caseNum = 1; caseNum <=nCases;caseNum++) {
		if (caseNum > 1)
			in = 0;
		int nFriends = input.ReadNext();
		int nConnections = input.ReadNext(); 
		//bitset<nFriends*BASE + BASE> in;
		//UnionFind uf(nFriends);
		//unordered_map<int, bool> myMap;
		//unordered_set<int> mySet;
		uf.fill(nFriends);

		for(i=0;i<nConnections;++i) {

			a = input.ReadNext() - 1;
			b = input.ReadNext() - 1;

			if (a>b) swap(a,b);
			prod = (a*30001+b);
			if (prod>MAX_SIZE) prod %= MAX_SIZE;
			//cout << "a " << a << " " << b << endl;
			if (!in[prod]) {
				in[prod] = 1;
				uf.Union(a,b);
			}

			/*
			auto it = mySet.insert(prod);
			if (it.second)
				uf.Union(a,b);
			*/
		}
		int ans = 0;
		for(i=0;i<nFriends;++i) {
			ans = max(ans, uf.subsets[i].total);
		}
		printf("%d\n", ans);
		//output.PrintUint(ans,'\n');
		
	}
	//output.Flush();
	return 0;
}