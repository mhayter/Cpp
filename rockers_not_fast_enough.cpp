#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <cassert>
using namespace std;

int nSongs,diskLen,nDisks;
vector<int>lens;
//map<pair<int,pair<int,int>>,int>myMap;

int memo[801][101][101];

int recurse(int place, int leftOver, int usedDisks) {
	if (usedDisks == nDisks) return 0;
	if (place>=nSongs) return 0;
	if (leftOver <= 0) return recurse(place,diskLen,usedDisks+1);
	//cout << place << " " << leftOver << " " << usedDisks << endl;
	if (memo[place][leftOver][usedDisks]!=-1){
		//cout << "memo " << memo[place][leftOver][usedDisks] << endl;
		return memo[place][leftOver][usedDisks];
	}
	//grab current disk
	int v1=0;
	if (leftOver>lens[place]){
		v1 = recurse(place+1, leftOver-lens[place], usedDisks) + 1;
	} else if (leftOver == lens[place]) {
		v1 = recurse(place+1,diskLen,usedDisks+1) + 1;
	} else {
		if (usedDisks+1 <nDisks && diskLen>=lens[place])
			v1 = recurse(place+1,diskLen-lens[place], usedDisks+1) + 1;
	}
	//dont grab disk
	int v2=recurse(place+1,leftOver, usedDisks);
	
	return memo[place][leftOver][usedDisks]=max (v1,v2);
}
int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		cin >> nSongs >> diskLen >> nDisks;
		assert(nSongs <=800); assert(diskLen<=100); assert(nDisks<=100);
		lens.clear();
		for(int i=0;i<=nSongs;i++) {
			for(int j=0;j<=diskLen;j++) {
				for(int k=0;k<=nDisks;k++){
					memo[i][j][k] = -1;
				}
			}
		}		
		int len;
		for(int i=0;i+1<nSongs;i++) {
			char c; cin >> len>>c;
			lens.push_back(len);
		}
		cin >> len; lens.push_back(len);
		int maxSongs = recurse(0,diskLen,0);
		cout << maxSongs << endl;
	}
	return 0;
}
