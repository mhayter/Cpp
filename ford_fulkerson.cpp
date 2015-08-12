#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_set>
using namespace std;

//sixth fastest (tied for second) no optimizaiton attempt

#define db(x) cerr << #x << " = " << x << endl;

const int MAX_NODES = 110;
int flow[MAX_NODES][MAX_NODES]; //set
int cap[MAX_NODES][MAX_NODES]; //set

vector<int>adj[MAX_NODES]; //set 

int parent[MAX_NODES];//fset
bool visited[MAX_NODES]; //set 

const int INF = 1000000000;


int bfs (int n, int source, int sink) {
	for(int i=0;i<n;++i) visited[i] = false;
	int minCap = INF;
	queue<int> que;
	que.push(source);

	while (!que.empty()) {
		int u = que.front(); que.pop();
		//db(u);
		if (u == sink) {
			//return min cap on path
			int place = u;
			
			while (parent[place] != -1) {
				minCap = min(minCap, cap[parent[place]][place] - flow[parent[place]][place]);
				place = parent[place];
			}
			//db(minCap);
			return minCap;
		}
		//if (visited[u]) continue;
		visited[u] = true;
		for(int i=0;i<adj[u].size();++i) {
			int v = adj[u][i];

			if (cap[u][v] - flow[u][v] > 0 && !visited[v]) {
				visited[v] = true;
				parent[v] = u;
				que.push(v);
			}
		}
	}
	return minCap;
}	

int fordFulkerson(int n, int source, int sink) {
	//cerr << "in " << endl;
	for(int i=0;i<n;i++) { //zero based
		for(int j=0;j<n;j++) {
			flow[i][j] = 0;
		}
		parent[i] = -1;
	}
	//while ath form source to sink in Gf where capf(u,v)>0 for all (u,v) in p
	int minCap = INF;
	//cerr << minCap << endl;
	int totalFlow = 0;
	while ((minCap = bfs(n,source,sink)) != INF) {
		int place = sink;
		while (parent[place] != -1) {
			int u = parent[place];
			int v = place;

			flow[u][v] += minCap;
			flow[v][u] -= minCap;

			place = parent[place];
		}
		totalFlow += minCap;
	} 
	/*for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			cerr << flow[i][j] << " ";
		}
		cerr << endl;
	}
	*/
	return totalFlow;
}

int main() {
	ios_base::sync_with_stdio(false);
	int nNodes; cin >> nNodes;
	int caseNum = 1;
	while (true) {
		int source, sink, nEdges; cin >> source >> sink >> nEdges;
		--source; --sink; // to zerobased

		for(int i=0;i<nNodes;++i) {
			adj[i].clear();
			for(int j=0;j<nNodes;++j){
				cap[i][j] = 0;
			}
		}

		set<pair<int,int>> mySet;
		for(int i=0;i<nEdges;++i) {
			int u, v; cin >> u >> v;
			--u; --v; // to zerobased
			if (mySet.find(make_pair(u,v)) == mySet.end()) { // not found
				adj[u].push_back(v);
				adj[v].push_back(u);
			}

			int capacity; cin >> capacity;

			cap[u][v] += capacity;
			cap[v][u] = cap[u][v];
		}
		
		cout << "Network " << caseNum++ <<'\n';
		int flow = fordFulkerson(nNodes, source,sink);
		cout << "The bandwidth is " << flow << ".\n";
		cin >> nNodes;
		
		cout << '\n';
		if (nNodes == 0) break;
	}
	return 0;
}