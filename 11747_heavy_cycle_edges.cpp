#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

//tied #1 8/12/2015 0.000s

class UnionFind{
	private:
		struct Subset{
			#ifdef TOTAL
			Subset(int parent,int rank,int total) {
				this->parent = parent;
				this->rank = rank;
				this->total = total;
			}
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



const int MAX_EDGES = 25010;
struct Edge {
	Edge(){}
	Edge(int a,int b, int weight):
		u(a), v(b), w(weight)
	{}
	bool operator<(const Edge &rhs) const {
		return w < rhs.w;
	}
	int u,v,w;
};

Edge edges[MAX_EDGES];
int nEdges;


int main() {
	int nNodes; 
	ios_base::sync_with_stdio(false);
	while (cin >> nNodes >> nEdges) {
		if (nNodes == 0 && nEdges == 0 ) break;

		UnionFind uf(nNodes);
		for(int i=0;i<nEdges;++i) {
			int u,v,w; cin >> u >> v >> w;

			edges[i] = Edge(u,v,w);
		}

		sort(edges,edges+nEdges);

		vector<int> heavyWeights;
		for(int i=0;i<nEdges;++i) {

			int xroot = uf.find(edges[i].u);
			int yroot = uf.find(edges[i].v);
			if(xroot != yroot) {
				uf.Union(xroot,yroot);
			} else { // cycle
				heavyWeights.push_back(edges[i].w);
			}
		}
		if (heavyWeights.size()) {
			for(int i=0;i+1<(int)heavyWeights.size();++i) {
				cout << heavyWeights[i] << " "; 
			}
			int size = (int)heavyWeights.size() - 1;
			cout << heavyWeights[size] << '\n';
		} else {
			cout << "forest\n"; // is this right?
		}
	}
	return 0;
}