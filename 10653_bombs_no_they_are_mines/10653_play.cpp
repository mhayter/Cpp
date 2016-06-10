#include <bits/stdc++.h>
using namespace std;

//0.020s myqueue A_star
//0.030s correcting A_star!
//0.110s with hand built que and  no for loops
//0.180s sync_with_stdio(false)
//0.230s bfs


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
int nRows, nCols;

const int MAX_COLS = 1010;
const int MAX_ROWS = 1010;

int dy[] = {0,1,0,-1};
int dx[] = {1, 0,-1,0};
int grid[MAX_ROWS][MAX_COLS];
int ok[MAX_ROWS][MAX_COLS];

struct AstarState {
	AstarState(){}
	AstarState(int y, int x, int depth,int w):
		y(y), x(x), depth(depth),w(w){}

	friend bool operator<(const AstarState&rhs, const AstarState &lhs);
	friend bool operator==(const AstarState&rhs, const AstarState &lhs);
	int y;
	int x;
	int depth;
	int w;
};

bool operator<(const AstarState&rhs, const AstarState &lhs) {
	if (rhs.w < lhs.w) return true;
	if (rhs.w == lhs.w) {
		return rhs.depth < lhs.depth;
	}
	return false;
}
 bool operator==(const AstarState&rhs, const AstarState &lhs) {
 	if (rhs.y != lhs.y) return false;
 	if (rhs.x != lhs.x) return false;
 	if (rhs.depth != lhs.depth) return false;
 	if (rhs.w != lhs.w) return false;
 	return true;
 }

int MD(int sy, int sx, int ey, int ex) {
	return abs(ey-sy)+abs(ex-sx);
}


const int MY_QUE_SIZE = 2;

AstarState myQue[MY_QUE_SIZE][MAX_ROWS*MAX_COLS+100];
#define ADJUST\
		int v1 = temp.depth+1+ MD(ey,ex,ny,nx);\
		if (grid[ny][nx] == 0 || grid[ny][nx] > v1){\
			grid[ny][nx] = v1;\
			if (ny == ey && nx == ex) return temp.depth+1;\
			if (v1 > temp.w) 	myQue[myQuePlace^1][qf[myQuePlace^1]++] = AstarState(ny,nx,temp.depth+1, v1);\
			else 				myQue[myQuePlace][qf[myQuePlace]++] = AstarState(ny,nx,temp.depth+1, v1);\
		}\


int qf[MY_QUE_SIZE];
int AstarMinimizeChecks(int sy, int sx, int ey, int ex) {
	qf[0] = 0;
	qf[1] = 0;
	if (sy == ey && sx==ex) return 0;
	myQue[MD(sy,sx,ey,ex)&1][qf[MD(sy,sx,ey,ex)&1]++] = AstarState(sy,sx,0, MD(sy,sx,ey,ex));
	int nElements  = 1;
	int myQuePlace = 0;
	while (nElements) {
		if (qf[myQuePlace] == 0) myQuePlace ^= 1;

		AstarState temp = myQue[myQuePlace][--qf[myQuePlace]]; 
		//cerr << temp.y << " " << temp.x << " " << temp.depth << " " << temp.w << endl;
		//--nElements;
		//if (temp.y == ey && temp.x == ex) return temp.depth;
		ok[temp.y][temp.x] = temp.depth+1;
		int ny, nx = temp.x;

		ny = temp.y + 1;
		if (ny < nRows && ok[ny][nx] == 0) {
			ADJUST;
		}
		ny = temp.y - 1;
		if (ny>=0  && ok[ny][nx] == 0) {
			ADJUST;
		}
		ny = temp.y;
		nx = temp.x+1;
		if (nx < nCols  && ok[ny][nx] == 0) {
			ADJUST;
		}
		nx = temp.x-1;
		if (nx >= 0  && ok[ny][nx] == 0) {
			ADJUST;
		}

	}
}

const int INF = 10000;
int main() {
	FastInput input;
	ios_base::sync_with_stdio(false);
	nRows = input.readNextUnsigned();
	nCols = input.readNextUnsigned();
	if (nRows == 0 && nCols == 0) return 0;;
	while (true) {
		int nRowsContainingBombs = input.readNextUnsigned();
		for(int i=0;i<nRowsContainingBombs;i++) {
			int row = input.readNextUnsigned();
			int nBombs = input.readNextUnsigned();
			for(int j=0;j<nBombs;j++) {
				int col = input.readNextUnsigned();
				ok[row][col] = 1;
			}
		}
		
		//cerr << "hello " << endl;
		int sy = input.readNextUnsigned();
		int sx = input.readNextUnsigned(); 
		int ey = input.readNextUnsigned();
		int ex = input.readNextUnsigned(); 
		
		AstarMinimizeChecks(sy,sx,ey,ex);
		cout << grid[ey][ex] << "\n";
		nRows = input.readNextUnsigned();
		nCols = input.readNextUnsigned();
		if (nRows == 0 && nCols == 0) break;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				ok[i][j] = grid[i][j] = 0;
			}
		}
		
		
		
	}
	return 0;
}