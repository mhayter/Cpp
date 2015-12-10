#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>
#include <sstream>
using namespace std;

class UnionFind{
private:
	struct Subset{
		int parent;
		int rank;
		int total;
	};
	vector<Subset>subsets;
	int nVerts;
public:
	UnionFind(int nVertices):nVerts(nVertices){
		for(int i=0;i<nVertices;i++) {
			subsets.push_back({i,0,1});
		}
	} 
	

int find(int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets[i].parent);
	return subsets[i].parent;
}

void Union(int x, int y) {
	int xroot = find(x);
	int yroot = find(y);
	
	if (xroot == yroot) return;
	int newTotal = subsets[xroot].total + subsets[yroot].total;
	subsets[xroot].total = subsets[yroot].total = newTotal;
	
	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	} else if (subsets[yroot].rank < subsets[xroot].rank) {
		subsets[yroot].parent = xroot;
	} else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}
};
int high=0;
unordered_map<string,int>myMap;
int getIndex(const string &s) {
	if (myMap.count(s))
		return myMap[s];
	else {
		return myMap[s]=high++;
	}
}


int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	string s;
	int nCases; cin >> nCases; getline(cin,s);
	getline(cin,s);
	while (nCases--) {
	int nVertices; cin >> nVertices;getline(cin,s);
	UnionFind uf(nVertices);
	int totalSuccess=0;
	int totalFail = 0;
	while (getline(cin,s) && !s.empty()) {
		
		
		if (cin.eof()) break;
		char op; int u, v;
		sscanf(s.c_str(),"%c %d %d",&op,&u,&v); // so much faster thans sstream
		--u;--v;


		if (op == 'c'){
			uf.Union(u,v);
		} else {
			totalSuccess+=(int)(uf.find(u) == uf.find(v));
			totalFail+=(int)(uf.find(u) != uf.find(v));
		}
	}
	cout << totalSuccess << "," << totalFail << '\n';
	if (!cin.eof()) cout << '\n';
	}
	return 0;
}
