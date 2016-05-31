#include <bits/stdc++.h>
using namespace std;

//0.080s fast run preallocate array 10,000,000
//0.100s fastio
//0.280s stdio(false)
//Begining 0.880s

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
        uint8_t m_buffer[32768*2];
        uint32_t m_data[16384*2];
        size_t m_dataOffset, m_dataSize;
        uint32_t m_v;
};

struct Edge {
    int u,v,w;
    Edge(){}
    Edge(int a,int b,int co) :
        u(a),v(b), w(co)
    {}
    friend bool operator<(const Edge &a, const Edge &b);
};

bool operator<(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

const int SIZE = 100000;

int par[SIZE];
int Rank[SIZE];

int set_find(int a) {
    if(a==par[a])
        return a;
    return(par[a]=set_find(par[a]));
}
void link(int x,int y) {
    if (Rank[x] < Rank[y]) {
        par[x] = y;
    } else if (Rank[y] < Rank[x]) {
        par[y] = x;
    } else {
        par[y] = x;
        Rank[x]++;
    }
}
void ini(int n) {
    for(int i=0; i<=n; i++) {
        par[i]=i;
        Rank[i] = 0;
    }
}

const int INF = 1000000000;

const int MAX_EDGES = 10000000;
Edge edges[MAX_EDGES];

int main() {
	int nCities, nRoads; 
	ios_base::sync_with_stdio(false);
	FastInput input;
	while (true) {
		nCities = input.readNextUnsigned();
		nRoads = input.readNextUnsigned();
		if (nCities == 0 && nRoads == 0) break;
		
        //assert(nRoads < 7000000);
        //vector<Edge> edges;
		for(int i=0;i<nRoads;i++) {
			int u = input.readNextUnsigned();
			int v = input.readNextUnsigned();
			int w = input.readNextUnsigned();
			edges[i] = Edge(u,v,w);
			//assert(w < 100000);
		}
		ini(nCities);

		sort(edges, edges+nRoads);

		int maxW = 0;
		int nConnected = 0;
		for(int i=0;i<nRoads;i++) {
			int xroot = set_find(edges[i].u);
			int yroot = set_find(edges[i].v);
			if (xroot != yroot) {
                link(xroot,yroot);
                int w = edges[i].w;
                nConnected++;
                if (w > maxW) maxW = w; 
            }
		}
		if (nConnected + 1 == nCities)
			cout << maxW << "\n";
		else cout << "IMPOSSIBLE\n";
	}

	return 0;
}