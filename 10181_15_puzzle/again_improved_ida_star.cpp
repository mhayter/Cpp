#include <iostream>
#include <algorithm>
using namespace std;
//#define DEBUG
/*
Right 0.002
*/

//Heuristics
#define PREV
//#define INADMISSIBLE

int MDist[4][4][4][4];

class State {
public:
	State() { 
		zx=zy=index=hash=myEstimate-1;
	}
	State (const State &rhs) {
		for(int i=0;i<ROWS;i++) 
			for(int j=0;j<COLS;j++)
				this->grid[i][j] = rhs.grid[i][j];
		zy=rhs.zy;
		zx=rhs.zx;
		index = rhs.index;
		hash = rhs.hash;
		myEstimate = rhs.myEstimate;
	}
	State& operator= (State s) {
		swap(grid,s.grid);
		swap(zy,s.zy);
		swap(zx,s.zx);
		swap(index,s.index);
		swap(hash,s.hash);
		swap(myEstimate,s.myEstimate);
		return *this;
	}
	friend bool operator<(const State &lhs, const State &rhs);
	bool stateEqual(const State &rhs) const {
		for(int i=0;i<ROWS;i++)
			for(int j=0;j<COLS;j++) 
				if (grid[i][j] != rhs.grid[i][j] )
					return false;
		return true;
	}

	bool isSolvable() const {
		int a[ROWS*COLS] = {0};
		int k=0;
		int row=1;
		for(int i=0;i<ROWS;i++) 
			for(int j=0;j<COLS;j++) {
				if(this->grid[i][j]==0)
					row = i+1;	
				a[k++] = this->grid[i][j];
				
			}
		
		int inversions=0;
		for(int i=0;i<ROWS*COLS;i++) {
			for(int j=i+1;j<ROWS*COLS;j++) {
				if (a[i]==0 || a[j]==0) continue;
				if (a[i]>a[j]) inversions++;
			}
		}
		if ((4-(row-1)) % 2 == 0) return inversions % 2 == 1;
		else return inversions % 2 == 0;
		return ((inversions+row)%2==0);
	}
	static int MD (int dy, int dx, int y, int x) {
		return abs(dy-y) + abs(dx-x);
	}

	//only for initial estimate
	int estimate() {
		int total=0;
		for(int i=0;i<ROWS;i++) {
			for(int j=0;j<COLS;j++) {
				if (this->grid[i][j]){
					int v= this->grid[i][j]-1;
					int srow = v/COLS;
					int scol = v%ROWS;
					total+=MD(i,j,srow,scol);
				}
			}
		}
		return this->myEstimate=total;
	}

	void adjust(int ny,int nx,int desty,int destx) {
		myEstimate += MDist[desty][destx][zy][zx]-MDist[desty][destx][ny][nx];
	}
	//change sor no recalc
	void undoAdjust(int ny, int nx,int desty,int destx) {
		myEstimate += MDist[desty][destx][ny][nx] - MDist[desty][destx][zy][zx];
	}

	int getHash () const {
		long long hash=0;
		long long product = 1;
		for(int i=0;i<ROWS;i++) {
			for(int j=0;j<COLS;j++) {
				hash = (hash + this->grid[i][j]*product) % 	MOD;
				product = (product * 31) % MOD;
			}
		}
		return hash;
	}

	long long  newHash() const {
		long long hash = 0;
		for(int i=0;i<ROWS;i++) {
			for(int j=0;j<COLS;j++) {
				hash = grid[i][j]+hash*7;
			}
		}
		return hash;
	}
	void print() {
		for(int i=0;i<ROWS;i++) {
			for(int j=0;j<COLS;j++) {
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	const static int MOD = 999999937; // BIG PRIME < 1E9
	const static int ROWS = 4;
	const static int COLS = 4;
	const static int DEPTH_LIMIT = 50; //50

	int grid[ROWS][COLS]; 
	int zy,zx;
	int index;
	int hash;
	int myEstimate;
};

bool operator<(const State &lhs, const State &rhs) {
	return lhs.zy < rhs.zy;
}
State dest;

//absolute estimate 
const int INF = 100;
const int FOUND = 999;
const int NOT_FOUND = -1;

const int dy[] = {1,0, -1, 0};
const int dx[] = {0, 1,0, -1};

const char dir[]="DRUL";
const char idir[]="ULDR";

char ans[100];
/*
unordered_map<long long, vector<State>> memo;

bool okay(State &cur) {
	if (memo[cur.hash].size()) {
		for(auto &x: memo[cur.hash]) 
			if (x.stateEqual(cur)) 
				return false;
	}
	return true;
}
*/
int bound;

/*#define mySwap(a,b) { 	(a)^=(b); \
						(b)^=(a); \
						(a)^=(b); \
					}
*/
inline void mySwap(int &a, int &b) {
	a^=b;
	b^=a;
	a^=b;
}

int search(State &cur, int g, char prevMove) {
	#ifdef INADMISSIBLE
	int f = g + 2*cur.myEstimate;
	#else
	int f = g + cur.myEstimate;
	#endif
	if (f>bound) return f;
	//if in memo
	if (cur.myEstimate == 0) {
		for(int i=0;i<g;i++) cout << ans[i];
		cout << "\n";
		return FOUND;
	}
	if (g>State::DEPTH_LIMIT) return INF;		
	int min = INF;
	int ny,nx;
	int destPlace, desty, destx;
	int t;
	//int temp1=grid[cur.zy][cur.zx];
	int temp2=cur.zy;
	int temp3=cur.zx;
	for(int i=0;i<4;i++) {
#ifdef PREV
		if (dir[i]=='U' && prevMove=='D') continue;
		if (dir[i]=='D' && prevMove=='U') continue;
		if (dir[i]=='L' && prevMove=='R') continue;
		if (dir[i]=='R' && prevMove=='L') continue;
#endif
		ny = cur.zy + dy[i];
		nx = cur.zx + dx[i];
		/// 0.0003s
		if (ny<State::ROWS && ny>=0 && nx<State::COLS && nx>=0) {
			//swap ny,nx with  cur.zy cur.zx
			/*
			int newIndex = ny*4+nx;
			int oldIndex = cur.zy*4+cur.zx;
			int newG = grid[newIndex/4][newIndex%4];
			int newHash = cur.hash - pow(7,15-(newIndex)) * newG + pow(7,15-oldIndex)*newG;
			swap(cur.hash,newHash);
			*/
				
				//swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
				//swap(cur.zy,ny); swap(cur.zx,nx);

				//cur.hash = cur.newHash();
			destPlace = cur.grid[ny][nx] - 1;
			desty = destPlace >> 2;
			destx = destPlace & 0x3;
			
			cur.adjust(ny,nx,desty,destx);

			//mySwap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			//mySwap(cur.zy,ny);
			//mySwap(cur.zx,nx);
			cur.grid[cur.zy][cur.zx] = cur.grid[ny][nx];
			cur.grid[ny][nx] = 0;
			//swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			cur.zy = ny;
			cur.zx = nx;
			//get new hash instantly
			ans[g]=dir[i];
			
			t = search(cur,g+1,dir[i]);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;

			//mySwap(cur.zy,ny);
			//mySwap(cur.zx,nx);
			//mySwap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			cur.zy = temp2;
			cur.zx = temp3;
			cur.grid[ny][nx] = cur.grid[cur.zy][cur.zx];
			cur.grid[cur.zy][cur.zx] = 0;
			//swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			//mySwap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			cur.undoAdjust(ny,nx,desty,destx);
		}
	}
	return min;
}

int IDAstar(State &s) {
	bound = s.estimate();
	while (bound<=50) {
		int t = search(s,0,' ');
		//cout << "bound = " << bound << endl;
		if (t==FOUND) return FOUND;
		if (t==INF) return NOT_FOUND;
		bound = t;
	}
	//cout << "Too large." << endl;
	return NOT_FOUND;
}

void initDestination() {
	int val=1;
	for(int i=0;i<State::ROWS;i++) 
		for(int j=0;j<State::COLS;j++) 
			dest.grid[i][j]=val++;

	dest.grid[State::ROWS-1][State::COLS-1] = 0;
	dest.zy=State::ROWS-1; dest.zx=State::COLS-1;
}

void initMDist() {
	for(int i=0;i<State::ROWS;i++) {
		for(int j=0;j<State::COLS;j++) {
			for(int a=0;a<State::ROWS;a++) {
				for(int b=0;b<State::COLS;b++) {
					MDist[i][j][a][b] = State::MD(i,j,a,b);
				}
			}
		}
	}
}

int main() {
	//initDestination();
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	initMDist();
	for(int caseNum=1;caseNum<=n;caseNum++) {
		cerr << "caseNum " << caseNum << endl;
		State s;
		for(int i=0;i<State::ROWS;i++) {
			for(int j=0;j<State::COLS;j++){
				cin >> s.grid[i][j];
				if (s.grid[i][j]==0) {
					s.zy=i; s.zx = j;
				}
			} 
		}
		s.hash = s.newHash();
		s.index = -1;

		if (!s.isSolvable()) {
			cout << "This puzzle is not solvable." << endl;
		} else {
			int v = IDAstar(s);
			if (v == NOT_FOUND) {
				cout << "SHIT This puzzle is not solvable." << endl;
			}
		}
	}
	return 0;
}