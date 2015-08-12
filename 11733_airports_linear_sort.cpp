#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <bitset>
using namespace std;

//has nasty (BUG?) when not using total it's wrong
//should linear sort (COUNTING)

//#define COUNTING
//not adding edges >= A may be an error

#ifndef __MY_FAST_IO__
#define __MY_FAST_IO__
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
	uint32_t readNextUnsigned() {
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
#endif

int N;

int nComponents;
int weightTotal;
const int NUM_EDGES = 100010;

struct Edge {
	int w, u, v;
	friend bool operator<(const Edge &lhs, const Edge &rhs);
};

bool operator<(const Edge &lhs, const Edge &rhs) {
	return lhs.w < rhs.w;
}
#ifndef COUNTING
Edge edges[NUM_EDGES];
#endif
#define TOTAL
class UnionFind{
	private:
		struct Subset{
			#ifdef TOTAL
			Subset(int p,int r,int t) :
				parent(p), rank(r), total(t)
			{}
			int parent;
			int rank;
			int total;
			#else 
			Subset(int parent,int rank) {
				this->parent = parent;
				this->rank = rank;
			}
			int parent;
			int rank;
			#endif
		};
		vector<Subset>subsets;
		int nVerts;
	public:
		UnionFind(int nVertices):nVerts(nVertices){
			for(int i=0;i<nVertices;i++) {
				#ifdef TOTAL 
				subsets.push_back(Subset(i,0,1));
				#else
				subsets.push_back(Subset(i,0));
				#endif
			}
		} 
		
		int find(int i) {
			if (subsets[i].parent != i)
				subsets[i].parent = find(subsets[i].parent);
			return subsets[i].parent;
		}

		void Union(int xroot, int yroot) {
			if (subsets[xroot].rank < subsets[yroot].rank) {
				subsets[xroot].parent = yroot;
			} else if (subsets[yroot].rank < subsets[xroot].rank) {
				subsets[yroot].parent = xroot;
			} else {
				subsets[yroot].parent = xroot;
				subsets[xroot].rank++;
			}
			//int newTotal = subsets[xroot].total + subsets[yroot].total;
			//subsets[xroot].total = subsets[yroot].total = newTotal;
		}
};

const int MAX_WEIGHT = 10010;
#ifdef COUNTING
vector<pair<int,int>> edgesCounting[MAX_WEIGHT];
#endif
bitset<MAX_WEIGHT> mySet;

int main() {
	//ios_base::sync_with_stdio(false);
	FastInput input;
	int nCases = input.readNextUnsigned();
	for(int caseNum=1;caseNum<=nCases;++caseNum) {
		int N = input.readNextUnsigned();
		int M = input.readNextUnsigned();
		int A = input.readNextUnsigned();

		int nEdges = 0;
		#ifdef COUNTING
		int myMaxWeight = 0;
		int myMinWeight = 1000000;
		#endif
		for(int i=0;i<M;++i) {
			int u = input.readNextUnsigned();
			int v = input.readNextUnsigned();
			int w = input.readNextUnsigned();
			--u;--v;
			if (w >= A) continue;
			
			#ifdef COUNTING
			edgesCounting[w].push_back(make_pair(u,v));
			myMaxWeight = max(myMaxWeight, w);
			myMinWeight = min(myMinWeight, w);
			#else 
			edges[nEdges++] = {w,u,v};
			#endif
			//adj[v].push_back({u,w});
		}
		UnionFind uf(N);
		//sort in linear time
		#ifdef COUNTING
		weightTotal = 0;
		for(int weight = myMinWeight; weight<=myMaxWeight;++weight) {
			for(int j=0;j<edgesCounting[weight].size();++j) {
				int xroot = uf.find(edgesCounting[weight][j].first);
				int yroot = uf.find(edgesCounting[weight][j].second);
				if (xroot != yroot) {
					uf.Union(xroot,yroot);
					weightTotal += weight;
				}
			}
			edgesCounting[weight].clear();
		}
		#else
		weightTotal = 0;
		sort(edges,edges + nEdges); //stable sort breaks it
		for(int i=0;i<nEdges;++i) {
			int xroot = uf.find(edges[i].u);
			int yroot = uf.find(edges[i].v);

			if (xroot != yroot) {
				uf.Union(xroot,yroot);
				weightTotal += edges[i].w;
			}
		}
		#endif
		nComponents = 0;
		for(int i=1;i<=N;++i) {
			int place = uf.find(i);
			if (!mySet[place]) {
				++nComponents;
				mySet[place] = 1;
			}
		}
		mySet = 0;
		int ans = weightTotal + A * nComponents;
		cout << "Case #" << caseNum << ": " << ans << " " << nComponents << '\n';

	}
	return 0;
}