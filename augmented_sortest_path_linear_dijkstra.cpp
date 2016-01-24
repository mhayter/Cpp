#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <bitset>
#include <map>
using namespace std;


//kind of works
const int MAX_EDGES = 50010;
const int MAX_VERTICIES = 20010;

const int INF = 100000000;

struct Edge {
	Edge (int a,int b,int c) : v(a), w(b), id(c) {}
	int v;
	int w;
	int id;
};
vector< Edge > adj[MAX_VERTICIES];

//bitset<MAX_VERTICIES> inq[MAX_EDGES]; //edge list
unordered_map< int , bool> inq;
unordered_map< int, int> edge;

int d[MAX_VERTICIES];
int parent[MAX_VERTICIES];

int ASP(int source, int nVerts, int dest, int w_min) {
	//set all to false and inf for all edges
	inq.clear();
	edge.clear();
	for(int i=0;i<=nVerts;i++) {
		d[i] = INF;
		parent[i] = -1;
	}
	cerr << "before " << d[dest] << endl;
	d[source] = 0;

	queue <pair<int,Edge> > que; // u Edge {v, w, id}
	for(int i=0;i<adj[source].size();i++) {
		int v = adj[source][i].v;
		int w = adj[source][i].w;
		int id = adj[source][i].id;

		que.push(make_pair(source, Edge(v,w,id)));
		inq[id] = true;
		edge[id] = w;
	}
	
	while (!que.empty()) {
		int v = que.front().second.v;
		int p = que.front().first;
		int w = que.front().second.w;
		int pv_id = que.front().second.id; //init
		que.pop();

		int weight_v = edge[pv_id] - w_min;
		if (weight_v <= 0) {
			if (d[p] + w < d[v]) {
				d[v] = d[p] + w;
				parent [v] = p;
			
				for(int i=0;i<adj[v].size();i++) {
					int u = adj[v][i].v;
					int newW = adj[v][i].w;
					int vu_id = adj[v][i].id;

					if (inq.count(vu_id)==0) {
						if (d[v] + newW < d[u]) {
							que.push(make_pair(v, Edge(u,newW,vu_id)));
							inq[vu_id] = true;
							edge[vu_id] = newW + weight_v;
						}
					} else {
						if (edge.count(vu_id))
							edge[vu_id] = min( edge[vu_id], newW + weight_v);
						else 
							edge[vu_id] = newW + weight_v;
					}
				}
			}
		} else {
			if (d[p] + w < d[v]) {
				que.push(make_pair(p,Edge(v,w,pv_id)));
				edge[pv_id] = weight_v;
			}
		}
	}
	return d[dest];
}

int main() {
	int source = 0;
	int dest = 5;
	int nVerts = 5;
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		int nVerts, nEdges, source, dest;
		cin >> nVerts >> nEdges >> source >> dest;

		for(int i=0;i<nVerts;i++) {
			adj[i].clear();
		}

		int w_min = INF;
		for(int i=0;i<nEdges;i++) {
			int u,v,w;
			cin >> u >> v >> w;
			w_min = min(w_min, w);

			adj[u].push_back({v,w,i});
			adj[v].push_back({u,w,i});
		}
		int ans = ASP(source, nVerts, dest,w_min);

		cout << "Case #" << caseNum << ": ";
		if (ans == INF) {
			cout << "unreachable\n";
		} else {
			cout << ans << '\n';
		}
	}
	return 0;
}