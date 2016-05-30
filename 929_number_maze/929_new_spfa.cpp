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
#include <cassert>
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
const int SIZE = 1000*1000+10;

int nRows,nCols;
int dist[SIZE];

//int grid[1010][1010];
int weights[SIZE];

int getIndex(int y,int x) {
	return y*nCols + x;
}


#define AddIT \
	if (dist[u] + weights[nIndex] < dist[nIndex]) {\
		dist[nIndex] = dist[u] + weights[nIndex];\
		if (!inq[nIndex]) {\
			que.push_back(nIndex);\
			if (dist[nIndex] < dist[que.front()]) {\
				toPush = nIndex; que.pop_back();\
				que.push_front(toPush);\
			}\
			inq[nIndex] = 1;\
		}\
	}\

bitset<SIZE>inq;
int SPFA_SLF(int n, int source, int destination) {
	inq = 0;
	for(int i=0;i<=n;i++) {
		dist[i]=INF;
	}

	dist[source]=weights[source];
	deque<int>que;

	que.push_back(source);
	inq[source]=true;

	int u,v,w;
	int toPush;
	int avg;
	#ifdef LLL
	int tot = 0;
	#endif
	while (!que.empty()) {
		int u = que.front(); que.pop_front();
		inq[u] = 0;
		#ifdef LLL
		tot -= dist[u];
		#endif

		int nIndex = u + nCols;
		if (nIndex < n) {
			//assert(nIndex>=0 && nIndex <n);
			AddIT;	
		}
		if (u % nCols != (nCols-1)) {
			nIndex = u + 1;
			AddIT;
		}
		nIndex = u - nCols;
		if (nIndex >= 0) {
			//assert(nIndex>=0 && nIndex <n);
			AddIT;
		}
		if (u % nCols != 0) {
			nIndex = u - 1;
			//assert(nIndex>=0 && nIndex <n);
			AddIT;
		}

		/*
		for(int i=0;i<4;i++){
			v = x.second;
			w = x.first;

			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if (!inq[v]){
					//que.push(v);
					que.push_back(v);

					#ifdef LLL
					tot += dist[v];
					#endif

					#ifdef SLF
					//small label first SLF
					if (dist[v] < dist[que.front()]) {
						toPush = v; que.pop_back();
						que.push_front(toPush);
					}
					#endif
					#ifdef LLL
					avg = tot/que.size();
					while (dist[que.front()] > avg) {
						toPush = que.front(); que.pop_front();
						que.push_back(toPush);
					}
					#endif
					//if (qe == SIZE) qe = 0;
					inq[v]=true;
				}
			}
		}
		*/
	}
	/*
	for(int i=0;i<nRows;i++) {
		for(int j=0;j<nCols;j++) {
			printf("%d ", dist[getIndex(i,j)]);
		}
		printf("\n");
	}
	*/
	cerr << "first " << dist[nCols] << endl;
	return dist[destination];
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
		assert(nCols <= 1000);
		cerr << "nCols = "<< nCols << "\n";
		int nNodes = 0;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				weights[nNodes++] = input.ReadNext();
			}
		}
		int dest = nRows*nCols -1;
		printf("%d\n",SPFA_SLF(nRows*nCols,0, dest));
	}
	//cout <<"fart" << endl;
	//output.Flush();
	return 0;
}