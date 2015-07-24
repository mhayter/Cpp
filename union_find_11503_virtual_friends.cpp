#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Subset{
	int parent;
	int rank;
	int total;
};

int find(vector<Subset> &subsets, int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}

void Union(vector<Subset>&subsets, int x, int y) {
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);
	
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
	int nCases; cin >> nCases;
	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int length; cin >> length;
		high = 0;
		vector<pair<int,int>>adj;
		myMap.clear();
		
		for(int i=0;i<length;i++) {
			string s1, s2; cin >> s1 >> s2;
			int index1 = getIndex(s1);
			int index2 = getIndex(s2);
			
			adj.push_back(make_pair(index1,index2));
		}
		vector<Subset>subsets(high);
		for(int i=0;i<high;i++) {
			subsets[i].parent=i;
			subsets[i].rank=0;
			subsets[i].total=1;
		}
		
		for(int i=0;i<length;i++) {
			int u = adj[i].first;
			int v = adj[i].second;
			
			Union(subsets,u,v);
			cout << subsets[find(subsets,u)].total << endl;
		}
		//cout << endl;
	}
	return 0;
}
