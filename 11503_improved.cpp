#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//#5 8/12/2015 0.143s

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
	if (myMap.count(s))
		return myMap[s];
	else {
		return myMap[s]=high++;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

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
			cout << subsets[find(u)].total << '\n';
		}
		//cout << endl;
	}
	return 0;
}
