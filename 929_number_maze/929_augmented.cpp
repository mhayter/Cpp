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

#include <cstdio>
#include <cstring>
#include <cstdint>

//Library stolen from codechef
class FastInput {
	public:
	FastInput() {
		m_dataOffset = 0;
		m_dataSize = 0;
		m_v = 0x80000000;
	}
	uint32_t ReadNext() {
		if (m_dataOffset == m_dataSize) {
			int r = fread(m_buffer,1,sizeof(m_buffer),stdin);
			if (r <= 0) return m_v;
			m_dataOffset = 0;
			m_dataSize = 0;
			int i = 0;
			if (m_buffer[0] < '0') {
				if (m_v != 0x80000000) {
					m_data[m_dataSize++] = m_v;
					m_v = 0x80000000;
				}
				for (; (i < r) && (m_buffer[i] < '0'); ++i);
			}
			for (; i < r;) {
				if (m_buffer[i] >= '0') {
					m_v = m_v * 10 + m_buffer[i] - 48;
					++i;
				} else {
					m_data[m_dataSize++] = m_v;
					m_v = 0x80000000;
					for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
				}
			}
		}
		return m_data[m_dataOffset++];
	}
	public:
		uint8_t m_buffer[32768];
		uint32_t m_data[16384];
		size_t m_dataOffset, m_dataSize;
		uint32_t m_v;
};

const int INF = 1000000000;
const int SIZE = 1000*1000+10;

int nRows,nCols;
int dist[SIZE];

pair<int,int> myGraph[SIZE][4]; //v,id
int deg[SIZE];
int myGrid[SIZE];


//kind of works
const int MAX_EDGES = 50010;
const int MAX_VERTICIES = 20010;

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

int d[SIZE];
int parent[SIZE];

const int ADD_FACTOR = 0;

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

	//edges [0-9] need to add to make work so need to know depth
	queue < pair<pair<int,Edge>,int> > que; // u Edge {v, w, id}
	for(int i=0;i<deg[source];i++) {
		int v = myGraph[source][i].first;
		int w = myGrid[v];
		int id = myGraph[source][i].second;

		que.push(make_pair(make_pair(source, Edge(v,w,id)),1));
		inq[id] = true;
		edge[id] = w;
	}
	int minDepth = INF;
	while (!que.empty()) {
		int v = que.front().first.second.v;
		int p = que.front().first.first;
		int w = que.front().first.second.w;
		int pv_id = que.front().first.second.id; //init
		int depth = que.front().second;

		if (v == dest){ //found 
			minDepth = min(minDepth,depth);
		}
		que.pop();

		int weight_v = edge[pv_id] - w_min;
		if (weight_v <= 0) {
			if (d[p] + w < d[v]) {
				d[v] = d[p] + w;
				parent [v] = p;
			
				for(int i=0;i<deg[v];i++) {
					int u = myGraph[v][i].first;
					int newW = myGrid[u];
					int vu_id = myGraph[v][i].second;

					if (inq.count(vu_id)==0) {
						if (d[v] + newW < d[u]) {
							que.push(make_pair(make_pair(v, Edge(u,newW,vu_id)),depth+1));
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
				que.push(make_pair(make_pair(p,Edge(v,w,pv_id)),depth));
				edge[pv_id] = weight_v;
			}
		}
	}
	return d[dest] - ADD_FACTOR*minDepth;
}

void buildMyGraph(int nNodes) {
	//super node for begining
	deg[0]=0;
	myGraph[0][deg[0]++] = make_pair(1,0);
}

int main() {
	//ios_base::sync_with_stdio(false);

	FastInput input;
	//FastOutput output;

	int nCases = input.ReadNext();
	//int nCases; scanf("%d\n",&nCases);
	
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		int nNodes = 1;
		int w_min = INF; //max 10
		int nEdges = 1;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				//grid[i][j] = input.ReadNext();
				deg[nNodes] = 0;
				if (j-1>=0) // add it
					myGraph[nNodes][deg[nNodes]++] = make_pair(nNodes-1,nEdges++);
				if (j+1<nCols) 
					myGraph[nNodes][deg[nNodes]++] = make_pair(nNodes+1,nEdges++);
				if (i-1>=0)
					myGraph[nNodes][deg[nNodes]++] = make_pair(nNodes-nCols, nEdges++);
				if (i+1<nRows)
					myGraph[nNodes][deg[nNodes]++] = make_pair(nNodes+nCols, nEdges++);

				myGrid[nNodes] = input.ReadNext()+ADD_FACTOR;
				w_min = min (w_min,myGrid[nNodes]);
				nNodes++;
			}
		}
		
		//build graph
		buildMyGraph(nNodes); //takes 0.482s?

		cerr << "Done building" << endl;
		//output.PrintUint(dijkstraCrazyQueue(0, nNodes, nRows*nCols),'\n');
		printf("%d\n", ASP(0, nNodes, nRows*nCols,w_min));
		//printf("%d\n",SPFA_SLF(nNodes,0, nRows*nCols));
	}
	//cout <<"fart" << endl;
	//output.Flush();
	return 0;
}