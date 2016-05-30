#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <cctype>
#include <queue>
#include <bitset>
#include <vector>
#include <stack>
#include <unordered_map>
#include <ctime>
using namespace std;

#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdint>


//slow probably doing it wrong
#define PREV

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

const int SIZE = 1000*1000;

int nRows,nCols;
int dist[SIZE];

int grid[1010][1010];

//absolute estimate 
const int INF = 2010*9;
const int FOUND = 12345;
const int NOT_FOUND = -1;

const int dy[] = {1,0, -1, 0};
const int dx[] = {0, 1,0, -1};

const int add[] = {4,1,-4,-1};
const char dir[]="DRUL";
const char idir[]="ULDR";

int bound;

#define DOIT(direction)\
	int w = grid[ny][nx];\
	int alt = dist[uIndex] + w;\
	if (alt < dist[getIndex(ny,nx)]) {\
		dist[getIndex(ny,nx)] = alt;\
		int newIndex = (cirIndex + w) & CIRC_QUE_SIZE_MINUS_ONE;\
		circularQue[newIndex][cqsize[newIndex]++] = make_pair(ny,nx); \
		++nElements;\
	}\

int getIndex (int y,int x) {
	return y*nCols + x;
}
enum DIR {UP,DOWN,LEFT,RIGHT};

#define DO_UP\
	ny = u.first-1; nx= u.second;\
	if (ny >= 0) {\
		DOIT(UP);\
	}

#define DO_DOWN\
	ny = u.first+1; nx = u.second;\
	if (ny < nRows) {\
		DOIT(DOWN);\
	}

#define DO_LEFT\
	ny = u.first; nx = u.second-1;\
	if (nx>=0) {\
		DOIT(LEFT);\
	}

#define DO_RIGHT\
	ny = u.first; nx = u.second+1;\
	if (nx < nCols) {\
		DOIT(RIGHT);\
	}

int best[1010][1010];

int search(int y, int x, int weight, int g, char prevMove) {
	int f = weight + ((nRows-1)-y + (nCols-1)-x)/2;//estimate
	//cout << "f = " << f << endl;
	if (f>bound) return f;

	if (weight > 9*(2*nRows*nCols)) return INF;	
	if (weight > best[y][x]) return INF;
	if (weight< best[y][x]) best[y][x] = weight;
	//if in memo
	if (y == (nRows-1) && x == (nCols-1)) {
		cout << weight << "\n";
		return FOUND;
	}
	
	int min = INF;
	for(int i=0;i<4;i++) {
#ifdef PREV
		if (dir[i]=='U' && prevMove=='D') continue;
		if (dir[i]=='D' && prevMove=='U') continue;
		if (dir[i]=='L' && prevMove=='R') continue;
		if (dir[i]=='R' && prevMove=='L') continue;
#endif
		int ny = dy[i] + y;
		int nx = dx[i] + x;
		if (ny<nRows && ny>=0 && nx<nCols && nx>=0) {
			
			//do stuff here
			int t = search(ny, nx, weight + grid[ny][nx],g+1,dir[i]);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;

			//adjust
		}
	}
	return min;
}

int IDAstar() {
	bound = 0;
	while (true) {
		int t = search(0,0,0,0,' ');
		cout << "bound = " << bound << endl;
		if (t==FOUND) return FOUND;
		if (t==INF) return NOT_FOUND;
		bound += 5;
	}
}

int main() {
	//int start = clock();
	ios_base::sync_with_stdio(false);
	FastInput input;
	int nCases = input.ReadNext();

	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		int nNodes = 1;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = input.ReadNext();
				best[i][j] = INF;
			}
		}
		IDAstar();
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				cout << best[i][j] << " ";
			}
			cout << endl;
		}
	}
	//cout <<grid[0][0] << endl;
	//output.Flush();
	return 0;
}
