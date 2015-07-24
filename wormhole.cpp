/*
ID: mhayter1
PROB: wormhole
LANG: C++
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;


int ans;
vector<pair<int,int> >array;
map<pair<int,int>, bool>done;
int n;
int partner[13];
int onRight[13];
bool visited[13];

int goRight(int place) {
	return onRight[place];
}

int hasCycle() {
	//go right
	for(int i=0;i<n;i++) {
		int p = i;
		for(int j=0;j<n;j++) {
			int part = partner[p];
			p = goRight(part);
			if (p == -1)break;
		}
		if (p!=-1) return true;
	}
	return false;
}

void dfs(int ntaken) {
	//for(int i=0;i<n;i++) cout << partner[i] << " ";
		//cout << endl;
	if (ntaken==n) {
		if (hasCycle())ans++;
		return;
	}
	//make pairs
	int i,j;
	for(i=0;i<n;i++) 
		if (!visited[i]) break;
		
	for (j=i+1;j<n;j++) {
				if (!visited[j]) {
					int mn = min(i,j); int mx=max(i,j);
					//if (done.count(make_pair(mn,mx))) continue;
					//done[make_pair(mn,mx)] = true;
					partner[i] = j;
					partner[j] = i;
					visited[i] = visited[j] = true;
					dfs(ntaken+2);
					visited[i] = visited[j] = false;
					partner[i] = partner[j] = -1;
				}
			}
		
	
}



int main() {
	// your code goes here
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");
	ios_base::sync_with_stdio(false);
	fin >> n;
	

	for(int i=0;i<n;i++) {
		int x,y; fin >> x >> y;
		::array.push_back(make_pair(x,y));
		partner[i]=-1;
		onRight[i]=-1;
	}
	
	
	for (int i=0;i<n;i++) {
		int minDist = 2000000000;
		for(int j=0;j<n;j++) {
			//if is on right and is best
			if (::array[i].first < ::array[j].first && ::array[i].second == ::array[j].second) {
				int dist = ::array[j].first;
				if (dist < minDist) {
					onRight[i] = j;
					minDist = dist;
				}
			}
		}
	}
	for(int i=0;i<n;i++) cout << onRight[i] << " " ;
	cout << endl;
	dfs(0);
	fout << ans << endl;
	return 0;
}
