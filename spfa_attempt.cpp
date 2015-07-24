#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int SIZE=20000;
const int INF=1000000000;
int dist[SIZE];

//w,v
vector<pair<int,int>> adj[SIZE];

bool inq[SIZE];

int SPFA(int n, int source, int destination) {
	for(int i=0;i<=n;i++) {
		dist[i]=INF;
		inq[i] = false;
	}
	
	dist[source]=0;
	queue<int>que;
	que.push(source);
	inq[source]=true;
	
	while (!que.empty()) {
		int u = que.front();que.pop();
		inq[u] = false;
		
		for(int i=0;i<adj[u].size();i++) {
			int v = adj[u][i].second;
			int w = adj[u][i].first;
			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if (!inq[v]){
					que.push(v);
					inq[v]=true;
				}
			}
		}
	}
	return dist[destination];
}

int main() {
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int numCase=1;numCase<=nCases;numCase++) {
		int n,m,source,destination; cin >>n >>m>>source>>destination;
		for(int i=0;i<=n;i++) adj[i].clear();
		for(int i=0;i<m;i++) {
			int u, v, w; cin>>u>>v>>w;
			adj[u].push_back(make_pair(w,v));
			adj[v].push_back(make_pair(w,u));
		}
		SPFA(n,source,destination);
		cout << "Case #" << numCase <<": ";
		if(dist[destination]==INF) 
			cout << "unreachable" << endl;
		else 
			cout << dist[destination] << endl;
	}
	return 0;
}
