#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int INF = 1000000000;
const int SIZE = 20010;

vector<pair<int,int>>graph[SIZE];
int dist[SIZE];

void dijkstra(int source, int n, int m) {
	for(int i=0;i<n;i++) dist[i] = INF;
	
	set<pair<int,int>>que;
	dist[source]=0;
	que.insert(make_pair(0,source));
	
	while (!que.empty()) {
		int u = que.begin()->second;
		int w = que.begin()->first;
		que.erase(que.begin());
		
		for(auto &p:graph[u]) {
			int alt = dist[u] + p.first;
			int v = p.second;
			if (alt < dist[v]) {
				dist[v] = alt;
				que.insert(make_pair(dist[v],v));
			}
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int numCase=1;numCase<=nCases;numCase++) {
		int n,m,source,destination; cin >>n >>m>>source>>destination;
		for(int i=0;i<n;i++) graph[i].clear();
		for(int i=0;i<m;i++) {
			int u, v, w; cin>>u>>v>>w;
			graph[u].push_back(make_pair(w,v));
			graph[v].push_back(make_pair(w,u));
		}
		dijkstra(source,n,m);
		cout << "Case #" << numCase <<": ";
		if(dist[destination]==INF) 
			cout << "unreachable" << endl;
		else 
			cout << dist[destination] << endl;
	}
	return 0;
}
