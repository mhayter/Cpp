#include <bits/stdc++.h>
using namespace std;


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

struct State {
	State(){}
	State(int y, int x, int w):
		y(y), x(x), w(w){}
	int y;
	int x;
	int w;
};


const int MAX_COLS = 1010;
const int MAX_ROWS = 1010;

int dy[] = {0,1,0,-1};
int dx[] = {1, 0,-1,0};
int grid[MAX_ROWS][MAX_COLS];
int ok[MAX_ROWS][MAX_COLS];

//deque<State>que;

State que[2*MAX_COLS*MAX_ROWS];
int qf;
int qb;

int bfs(int sy, int sx, int ey, int ex) {
	//que.clear();
	qf=qb= 0;
	que[qf++] = State(sy,sx,0);
	//que.push_front(State(sy,sx,0));
	while (qf!=qb) {
		State &temp = que[qb++]; 
		//assert (qf < 2*MAX_COLS*MAX_ROWS);
		//cerr << temp.y << " " << temp.x << " " << temp.w << endl;

		if (temp.y == ey && temp.x == ex) return temp.w;
		if (ok[temp.y][temp.x] !=0) continue;
		ok[temp.y][temp.x] = temp.w+1;

		int ny, nx = temp.x;

		ny = temp.y + 1;
		if (ny < nRows && ok[ny][nx] == 0) {
			que[qf++] = State(ny,nx,temp.w+1);
		}

		ny = temp.y - 1;
		if (ny>=0  && ok[ny][nx] == 0) {
			que[qf++] = State(ny,nx,temp.w+1);
		}
		ny = temp.y;
		nx = temp.x+1;
		if (nx < nCols  && ok[ny][nx] == 0) {
			que[qf++] = State(ny,nx,temp.w+1);
		}
		nx = temp.x-1;
		if (nx >= 0  && ok[ny][nx] == 0) {
			que[qf++] = State(ny,nx,temp.w+1);
		}
		/*
		for(int i=0;i<4;i++) {
			int ny = temp.y + dy[i];
			int nx = temp.x + dx[i];

			if (ny>=0 && nx>=0 && ny<nRows && nx < nCols && ok[ny][nx]==0) {
				//que.push_front(State(ny,nx,temp.w+1));
				que[qf++] = State(ny,nx,temp.w+1);
			}
		}
		*/
	}
}

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
deque<AstarState> myQue[MY_QUE_SIZE];


int Astar(int sy, int sx, int ey, int ex) {
	//multiset<AstarState>que;

	myQue[0].clear();
	myQue[1].clear();

	myQue[MD(sy,sx,ey,ex)&1].push_front(AstarState(sy,sx,0, MD(sy,sx,ey,ex)));
	//que.insert(AstarState(sy,sx,0, 5*MD(sy,sx,ey,ex)/3));
	int nElements  = 1;
	int myQuePlace = 0;
	while (nElements) {
		if (myQue[myQuePlace].size() == 0) myQuePlace ^= 1;

		//AstarState temp = *que.begin(); que.erase(que.begin());
		AstarState temp = myQue[myQuePlace].front(); myQue[myQuePlace].pop_front(); 
		/*cerr << "Removed " << temp.y << " " << temp.x << " " << temp.depth << " " << temp.w << endl;
		//if (temp.y == 1 && temp.x == 0) cerr << "OOOOOOOOOOOOOOOOBINGOOOOOOOOOOOOOO" << endl;
		cerr << "printing set" << endl;
		for (auto x: que) {
			cerr << x.y <<" " << x.x << " " << x.depth << " " << x.w << endl;
		}
		cerr << endl;
		*/
		if (temp.y == ey && temp.x == ex) return temp.depth;
		//if (grid[temp.y][temp.x] !=0) continue;
		ok[temp.y][temp.x] = temp.depth+1;

		for(int i=0;i<4;i++) {
			int ny = temp.y + dy[i];
			int nx = temp.x + dx[i];

			if (ny>=0 && nx>=0 && ny<nRows && nx < nCols && ok[ny][nx]==0) {
				int v1 = temp.depth+1+ MD(ey,ex,ny,nx)/3;
				//cerr << ny << " " <<nx << " newdepth " << temp.depth+1 <<" " << temp.depth+1+ MD(ey,ex,ny,nx)<< endl;
				if (grid[ny][nx] > v1){

					//cerr << "Added " << ny << " " << nx << endl;
					grid[ny][nx] = v1;
					if (ny == ey && nx == ex) return temp.depth+1;
					//que.insert(AstarState(ny,nx,temp.depth+1, v1));
					if (v1 > temp.w) {
						myQue[myQuePlace^1].push_front(AstarState(ny,nx,temp.depth+1, v1));
					} else {
						myQue[myQuePlace].push_front(AstarState(ny,nx,temp.depth+1, v1));
					}
					/*cerr << "After added printing set" << endl;
					for (auto x: que) {
						cerr << x.y <<" " << x.x << " " << x.depth << " " << x.w << endl;
					}
					cerr << endl;
					*/
				}
			}
		}
	}
}

const int INF = 10000;
int main() {
	FastInput input;
	ios_base::sync_with_stdio(false);
	while (true) {
		nRows = input.readNextUnsigned();
		nCols = input.readNextUnsigned();
		if (nRows == 0 && nCols == 0) break;
		int nRowsContainingBombs = input.readNextUnsigned();
		for(int i=0;i<nRowsContainingBombs;i++) {
			int row = input.readNextUnsigned();
			int nBombs = input.readNextUnsigned();
			for(int j=0;j<nBombs;j++) {
				int col = input.readNextUnsigned();
				ok[row][col] = 1;
			}
		}
		/*
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = INF;
			}
		}
		*/
		cerr << "hello " << endl;
		int sy = input.readNextUnsigned();
		int sx = input.readNextUnsigned(); 
		int ey = input.readNextUnsigned();
		int ex = input.readNextUnsigned(); 
		cerr << sy << " " << sx << " " << ey << " " << ex << endl;
		cout << bfs(sy,sx,ey,ex) << "\n";
		//Astar(sy,sx,ey,ex);
		//cout << grid[ey][ex] << "\n";
		/*
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}*/
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				ok[i][j] = 0;
			}
		}
		//memset(grid,0, sizeof(grid));
		
		
		
	}
	return 0;
}