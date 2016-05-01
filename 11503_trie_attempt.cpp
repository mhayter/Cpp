#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <cstdio>
#include <cstring>

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
Subset *mySubsets;

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

const int ALPHABET_SIZE = 52;
class Node {
public:
	Node () {
		for(int i=0;i<ALPHABET_SIZE;++i) array[i]=0;
		hashIndex = -1;
	}
	int hashIndex;
	Node *array[ALPHABET_SIZE];
};



class Trie{
public:
	Trie():curIndex(0) {
		hashIndexes.reserve(MAX_FRIENDS);
	}	
	void reset() {
		//reset hashIndex but retain memory
		for(auto &x:hashIndexes) {
			x->hashIndex = 0;
		}
		hashIndexes.clear();
		curIndex = 0;
	}
	//rather than update number in
	//return "hash index" for union-find algo 
	int insert(const char *s) {
		Node *place = &head;
		for (int i=0; s[i]>='A';++i) { //assum only space and alphas
			int index;
			if (s[i]>='a')
				index = s[i]-'a';
			else 
				index = s[i]-'A';

			if (place->array[index]==0) {
				place->array[index] = new Node;
			} 
			place = place->array[index];
		}
		if (place->hashIndex == -1) {
			//new element/ new index
			place->hashIndex = curIndex++;
		}
		return place->hashIndex;
	}
	
	int find(const char *s) {
		Node *place = &head;
		for(int i=0;s[i]>='A';++i) {
			int index;
			if (s[i]>='a')
				index = s[i]-'a';
			else 
				index = s[i]-'A';
			if (place->array[index] == 0) return 0;
			place = place->array[index];
		}
		return place->hashIndex;
	}
	Node head;	
	int curIndex;
	vector<Node *> hashIndexes;
};


Trie trie;

int main() {
	char line[80];
	FastOutput output;
	int nCases;
	scanf("%d\n", &nCases);
	//gets(line);
	//sscanf(line, "%d\n", &nCases);

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int length; 
		scanf("%d\n", &length);
		//gets(line);
		//sscanf(line, "%d\n", &length);

		nItems = 0;
		Subset subsets[length+100];//not technically correct?
		mySubsets = subsets;

		for(int i=0;i<length;i++) {

			char *s1 = new char[21]{'\0'};
			char *s2 = new char[21]{'\0'};

			scanf("%s %s\n", s1,s2);
			//gets(line);
			//sscanf(line, "%s %s\n", s1,s2);
			int index1 = trie.insert(s1);
			int index2 = trie.insert(s2);
			
			//printf ("%d %d\n", index1, index2);
			Union(index1,index2);

			output.PrintUint(subsets[find(index1)].total,'\n');
		}
		if (caseNum < nCases) {
			trie.reset();
		}
	}
		
	return 0;
}