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

// #2 0.126s macro + no forloop check
// #3 0.146s move constructor + save index 
// #3 0.153s dynamic graph construction
// now #5 0.215s -> 0.206s
// change initialization from fastest crazy queue
// no repeats visited = 0!

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

int grid[1010][1010];

const int CIRC_QUE_SIZE = 10;
deque<pair<int,int> > circularQue[CIRC_QUE_SIZE];
bitset<SIZE>visitied;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

#define DOIT \
	int w = grid[ny][nx];\
	int alt = dist[uIndex] + w;\
	if (alt < dist[getIndex(ny,nx)]) {\
		dist[getIndex(ny,nx)] = alt;\
		int newIndex = cirIndex + w;\
		if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;\
		circularQue[newIndex].push_front(make_pair(ny,nx)); \
		++nElements;\
	}\

int getIndex (int y,int x) {
	return y*nCols + x;
}

int dijkstraCrazyQueueCreateNodes(pair<int,int> source, int n,pair<int,int> dest) {
	for(int i=0;i<n;i++){ dist[i] = INF; }
	visitied = 0;
	for(int i=0;i<CIRC_QUE_SIZE;i++) circularQue[i].clear();
	int cirIndex=0;
	int nElements = 0;

	dist[0]=grid[0][0];
	circularQue[0].push_front(source);
	++nElements;
	
	while (nElements) {
		while (circularQue[cirIndex].empty()) {
			++cirIndex;
			if (cirIndex == CIRC_QUE_SIZE) cirIndex = 0;
		}
		pair<int,int> u = move(circularQue[cirIndex].front()); circularQue[cirIndex].pop_front();
		//cerr << "u " << u.first << " " << u.second << endl;
		if (u == dest) return dist[getIndex(dest.first,dest.second)];
		int uIndex = getIndex(u.first,u.second);
		if (visitied[uIndex]) continue;
		visitied[uIndex] = 1;
		--nElements;

		int ny, nx;
		ny = u.first+1; nx = u.second;
		if (ny < nRows) {
			DOIT;
		}
		ny = u.first-1; nx= u.second;
		if (ny >= 0) {
			DOIT;
		}
		ny = u.first; nx = u.second+1;
		if (nx < nCols) {
			DOIT;
		}
		ny = u.first; nx = u.second-1;
		if (nx>=0) {
			DOIT;
		}
	}
	return dist[getIndex(dest.first,dest.second)];
}

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#define fgets fgets_unlocked
#endif

int main() {
	FastInput input;

	int nCases = input.ReadNext();
	
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		int nNodes = 1;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = input.ReadNext();
			}
		}
		printf("%d\n", dijkstraCrazyQueueCreateNodes(make_pair(0,0), nRows*nCols, make_pair(nRows-1,nCols-1)));
	}
	//cout <<"fart" << endl;
	//output.Flush();
	return 0;
}