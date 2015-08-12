#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

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

const int MAX_CITIES = 755;
const int MAX_SIZE = MAX_CITIES*MAX_CITIES/2 + 10;
Edge edges[MAX_SIZE];
int nEdges;

struct Point{
	Point(){}
	Point(int a,int b): 
		x(a), y(b)
	{}
	int x,y;
	bool operator<(const Point &p) const {
		if (y < p.y) return true;
		if (y == p.y) {
			return x < p.x;
		}
		return false;
	}
};

#define sqr(x) ((x)*(x))

Point a[MAX_CITIES];
int nCities;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum <= nCases;++caseNum) {
		nEdges = 0;
		cin >> nCities;
		for(int i=0;i<nCities;++i) {
			cin >> a[i].x >> a[i].y;
		}
		for(int i=0;i<nCities;i++) {
			for(int j=i+1;j<nCities;++j) {
				int weight = sqr(a[i].x-a[j].x) + sqr(a[i].y-a[j].y);
				edges[nEdges++] = Edge(i+1,j+1,weight);
			}
		}
		int nCurrentRoads; cin >> nCurrentRoads;
		UnionFind uf(nCities+1);
		
		for(int i=0;i<nCurrentRoads;++i) {
			int u, v; cin >> u >> v;
			int xroot = uf.find(u);
			int yroot = uf.find(v);
			uf.Union(xroot,yroot); // no check for cycle
		}
		//cerr << "nEdges " << nEdges << endl;
		sort(edges, edges+nEdges);
		
		vector<pair<int,int>> extraRoads;
		for(int i=0;i<nEdges;++i) {
			int u = edges[i].u;
			int v = edges[i].v;
			int xroot = uf.find(u);
			int yroot = uf.find(v);

			if (xroot != yroot) {
				uf.Union(xroot,yroot);
				extraRoads.push_back(make_pair(u,v));
			}
		}
		if (extraRoads.size()){
			for(int i=0;i<extraRoads.size();++i) {
				cout << extraRoads[i].first << " " << extraRoads[i].second<< '\n';
			}
		} else {
			cout << "No new highways need\n";
		}
		if (caseNum < nCases) cout << '\n';
	}
	return 0;
}