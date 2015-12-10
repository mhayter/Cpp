#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
public:
	Node () {
		for(int i=0;i<26;++i) array[i]=0;
		colored = 0;
	}
	int colored;
	Node *array[26];
};


class Trie{
public:
	Trie() {	
	}
	void insert(const string &s) {
		Node *place = &head;
		int n = s.size();
		for (int i=0; i<n;++i) {
			int index = s[i]-'a';
			if (place->array[index]==0) {
				place->array[index] = new Node;
			} 
			place = place->array[index];
		}
		place->colored++;
	}
	int find(const string &s) {
		Node *place = &head;
		int n = s.size();
		for(int i=0;i<n;++i) {
			int index = s[i]-'a';
			if (place->array[index] == 0) return 0;
			place = place->array[index];
		}
		return place->colored;
	}
	Node head;	
};

int main() {
	string s;
	Trie trie;
	vector<string> array;
	ios_base::sync_with_stdio(false);
	unordered_map<string,int>myMap;
	while (cin >> s) {
		trie.insert(s);
		//++myMap[s];
		array.push_back(s);
	}
	int n = array.size();
	for(int i = 0; i<n;++i) {
		int xsize=array[i].size();

		string first = "";
		for(int j=1;j<xsize;++j) {
			first += array[i][j-1];
			if (!trie.find(first)) continue;
			string second = array[i].substr(j);
			
			if (trie.find(second)) {
				cout << array[i] << '\n';
			}
			
		}
	}
	return 0;
}
