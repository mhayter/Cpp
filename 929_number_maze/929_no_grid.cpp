#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <deque>
#include <list>
#include <forward_list>
#include <queue>
using namespace std;
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdint>

// 0.130s slower with no grid
// 0.126s slower with last move added pairs
// #2 0.119s remove visited
// #2 0.122s macro + no forloop check
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
		uint8_t m_buffer[32768*2];
		uint32_t m_data[16384*2];
		size_t m_dataOffset, m_dataSize;
		uint32_t m_v;
};

const int INF = 1000000000;
const int SIZE = 1000*1000;

int trueGridSize;//nRows * nCols;

int nRows,nCols;
int lastCol;

int dist[SIZE];

int weights[SIZE];

struct State {
	int ny;
	int nx;
};

const int CIRC_QUE_SIZE = 16;
const int CIRC_QUE_SIZE_MINUS_ONE = CIRC_QUE_SIZE - 1;
int circularQue[CIRC_QUE_SIZE][SIZE];// <y,x>,lastmove
int cqsize[CIRC_QUE_SIZE];

int cqs[CIRC_QUE_SIZE],cqe[CIRC_QUE_SIZE];
//bitset<SIZE>visitied;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

#define DOIT(direction)\
	int w = weights[newIndex];\
	int alt = dist[uIndex] + w;\
	if (alt < dist[newIndex]) {\
		dist[newIndex] = alt;\
		int newCircIndex = (cirIndex + w) & CIRC_QUE_SIZE_MINUS_ONE;\
		circularQue[newCircIndex][cqsize[newCircIndex]++] = newIndex; \
		++nElements;\
	}\

int getIndex (int y,int x) {
	return y*nCols + x;
}
enum DIR {UP,DOWN,LEFT,RIGHT};

#define DO_UP\
	newIndex = uIndex - nCols;\
	if (newIndex >= 0) {\
		DOIT(UP);\
	}

#define DO_DOWN\
	newIndex = uIndex + nCols;\
	if (newIndex < trueGridSize) {\
		DOIT(DOWN);\
	}

#define DO_LEFT\
	if ( uIndex % nCols != 0) {\
		newIndex = uIndex - 1;\
		DOIT(LEFT);\
	}

#define DO_RIGHT\
	if (uIndex % nCols != lastCol) {\
		newIndex = uIndex + 1;\
		DOIT(RIGHT);\
	}



int dijkstraCrazyQueueCreateNodes(pair<int,int> source, int n,pair<int,int> dest) {
	for(int i=0;i<n;i++){ dist[i] = INF; }
	//visitied = 0;
	for(int i=0;i<CIRC_QUE_SIZE;i++) {
		cqs[i] = cqe[i] = 0;
		cqsize[i] = 0;
	}
	int cirIndex=0;
	int nElements = 0;

	dist[0]=weights[0];
	circularQue[0][cqsize[0]++]= source.first * nCols + source.second; //START RIGHT OR DOWN aka 0
	++nElements;

	int myDest = dest.first*nCols + dest.second;
	
	while (nElements) {
		for(int i=0;i<cqsize[cirIndex];i++) {
			int uIndex = circularQue[cirIndex][i];//pop front
			if (uIndex == myDest) return dist[myDest];
			--nElements;

			int newIndex;
			DO_RIGHT;
			DO_DOWN;
			DO_LEFT;
			DO_UP
		}
		cqsize[cirIndex] = 0;
		++cirIndex;
		cirIndex &= CIRC_QUE_SIZE_MINUS_ONE;
	}
	return dist[myDest];
}

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#define fgets fgets_unlocked
#endif

FastInput input;

int main() {
	//int start = clock();
	ios_base::sync_with_stdio(false);
	
	int nCases = input.ReadNext();
	
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		trueGridSize = nRows * nCols;
		lastCol = nCols -1;

		for(int i=0;i<trueGridSize;i++) {
			weights[i] = input.ReadNext();
		}
		//cerr << clock() -start << endl;
		cout << dijkstraCrazyQueueCreateNodes(make_pair(0,0), nRows*nCols, make_pair(nRows-1,nCols-1)) << "\n";
	}
	//cout <<grid[0][0] << endl;
	//output.Flush();
	return 0;
}