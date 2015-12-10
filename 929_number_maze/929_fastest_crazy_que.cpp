#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <deque>
#include <list>
#include <forward_list>
#include <queue>
using namespace std;

#include <cstdio>
#include <cstring>
#include <cstdint>

//have no idea runs 0.348s one time upto 0.41s
//now #5 0.215s

#define SLF
//#define LLL

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
const int SIZE = 1000*1000;

int nRows,nCols;
int dist[SIZE];

int myGraph[SIZE][4];
int deg[SIZE];
int myGrid[SIZE];

struct myQue {
	int qb;
	int qe;

};

const int CIRC_QUE_SIZE = 10;
deque<int> circularQue[CIRC_QUE_SIZE];

int dijkstraCrazyQueueCreateNodes(int source, int n,int dest) {
	for(int i=0;i<n;i++) dist[i] = INF;
	for(int i=0;i<CIRC_QUE_SIZE;i++) circularQue[i].clear();
	int cirIndex=0;
	int nElements = 0;

	dist[source]=0;
	//que.insert(make_pair(0,source));
	circularQue[0].push_front(source);
	++nElements;
	
	while (nElements) {
		//int u = que.begin()->second;
		//int w = que.begin()->first;
		//if (cirIndex == 10) cirIndex = 0;
		while (circularQue[cirIndex].empty()) {
			++cirIndex;
			if (cirIndex == CIRC_QUE_SIZE) cirIndex = 0;
		}
		int u = circularQue[cirIndex].front(); circularQue[cirIndex].pop_front();
		if (u == dest) return dist[dest];
		//int w = circularQue[cirIndex]
		//cerr <<"u " << u <<" is popped" << endl;

		//que.erase(que.begin());
		--nElements;
		
		for(int i= 0;i<deg[u];++i) {
			//get neighbors weights
			int v = myGraph[u][i];
			int w = myGrid[v];

			int alt = dist[u] + w;
			
			if (alt < dist[v]) {
				dist[v] = alt;
				//que.insert(make_pair(dist[v],v));
				int newIndex = cirIndex + w;
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;

				circularQue[newIndex].push_front(v); 
				++nElements;
			}
		}
	}
	return dist[dest];
}

void buildMyGraph(int nNodes) {
	//super node for begining
	deg[0]=0;
	myGraph[0][deg[0]++] = 1;
}

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#define fgets fgets_unlocked
#endif

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
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				//grid[i][j] = input.ReadNext();
				deg[nNodes] = 0;
				if (j-1>=0) // add it
					myGraph[nNodes][deg[nNodes]++] = nNodes-1;
				if (j+1<nCols) 
					myGraph[nNodes][deg[nNodes]++] = nNodes+1;
				if (i-1>=0)
					myGraph[nNodes][deg[nNodes]++] = nNodes-nCols;
				if (i+1<nRows)
					myGraph[nNodes][deg[nNodes]++] = nNodes+nCols;

				myGrid[nNodes++] = input.ReadNext();
			}
		}
		
		//build graph
		buildMyGraph(nNodes); //takes 0.482s?

		//output.PrintUint(dijkstraCrazyQueue(0, nNodes, nRows*nCols),'\n');
		printf("%d\n", dijkstraCrazyQueueCreateNodes(0, nNodes, nRows*nCols));
		//printf("%d\n",SPFA_SLF(nNodes,0, nRows*nCols));
	}
	//cout <<"fart" << endl;
	//output.Flush();
	return 0;
}