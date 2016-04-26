#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <cstdio>
#include <cstring>

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
pair<int,int>adj[MAX_FRIENDS];
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
int high=0;
unordered_map<string,int>myMap;
int getIndex(const string &s) {
	auto myIterator = myMap.find(s);
	if (myIterator != myMap.end())
		return myIterator->second;
	else {
		return myMap[s]=high++;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	myMap.reserve(MAX_FRIENDS);
	FastOutput output;

	int nCases; cin >> nCases;
	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int length; cin >> length;
		high = 0;
		
		myMap.clear();
		for(int i=0;i<length;i++) {
			string s1, s2; cin >> s1 >> s2;
			int index1 = getIndex(s1);
			int index2 = getIndex(s2);
			
			adj[i] = make_pair(index1,index2);
		}
		for(int i=0;i<high;i++) {
			subsets[i].parent=i;
			subsets[i].total=1;
		}
		
		for(int i=0;i<length;i++) {
			int u = adj[i].first;
			int v = adj[i].second;
			
			Union(u,v);
			output.PrintUint(subsets[find(u)].total,'\n');
			//cout << subsets[find(u)].total << '\n';
		}
		//cout << endl;
	}
	return 0;
}
