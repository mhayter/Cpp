#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;

//cert #1 0.006s (fast server)
//multiple attempts at improvement
//--fread didn't help 
//--not using aLen didnt help
//--using fwrite instead of puts no help

class Node {
public:
	Node () {
		for(int i=0;i<26;++i) array[i]=0;
		colored = 0;
	}
	int colored;
	Node *array[26];
};
const int SIZE = 120010;
const int SECOND_SIZE = 35;
char array[SIZE][SECOND_SIZE];
//int aLen [SIZE];
//bool worked[SIZE];
bitset<SIZE> worked;


class Trie{
public:
	Trie() {	
	}
	void insert(const char *s) {
		Node *place = &head;
		for (int i=0; s[i]>='a';++i) {
			int index = s[i]-'a';
			if (place->array[index]==0) {
				place->array[index] = new Node;
			} 
			place = place->array[index];
		}
		place->colored++;
	}
	
	int find(const char *s) {
		Node *place = &head;
		for(int i=0;s[i]>='a';++i) {
			int index = s[i]-'a';
			if (place->array[index] == 0) return 0;
			place = place->array[index];
		}
		return place->colored;
	}
	int find(const char *s,int nChars) {
		Node *place = &head;
		for(int i=0;i<nChars;++i) {
			int index = s[i]-'a';
			if (place->array[index] == 0) return 0;
			place = place->array[index];
		}
		return place->colored;
	}
	Node head;	
};

char buff[SIZE*SECOND_SIZE+10];
int n;
//#include <iostream>
Trie trie;
void readAll() {
	int r = fread(buff,1,sizeof(buff), stdin);
	for(int i=0;i<r;++i) {
		//while >='a'
		int len = 0;
		while (buff[i]>='a') {
			array[n][len++] = buff[i++];
		}
		trie.insert(array[n]);
		//std::cerr << "#" << array[n] << "#\n";
		//aLen[n] = len;
		++n;
	}
}

char oBuffer [SIZE*SECOND_SIZE+10];
int oBufferPlace;

int main() {
	//Trie trie;
	//read 
	readAll();
	/*
	while (fgets(array[n], SECOND_SIZE, stdin) != 0) {
		aLen[n] = strlen(array[n]) - 1;
		trie.insert(array[n]);
		array[n][aLen[n]] = '\0'; 
		++n;
	}
	*/
	for(int i = 0; i<n;++i) {
		//int xsize = aLen[i];

		for(int j=1;array[i][j];++j) {
			if (!trie.find(array[i],j)) continue;
			char *place = (array[i]+j);			
			if (trie.find(place)) {
				worked[i]=true;
			}
		}
	}
	for(int i=0;i<n;++i) if (worked[i]) {
		int j = 0;
		while (array[i][j])
			oBuffer[oBufferPlace++] = array[i][j++];
		oBuffer[oBufferPlace++] = '\n';
	} 
	fwrite(oBuffer,1,oBufferPlace,stdout);
	return 0;
}
