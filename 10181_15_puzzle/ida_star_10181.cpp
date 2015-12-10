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
//#define DEBUG

#define PREV

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
	int MD (int dy, int dx, int y, int x) const {
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

	void adjust(int ny,int nx) {
		int destPlace = grid[ny][nx] - 1;
		int desty = destPlace / 4;
		int destx = destPlace % 4;
		myEstimate += MD(desty,destx,zy,zx);
		myEstimate -= MD(desty,destx,ny,nx);
	}
	//change sor no recalc
	void undoAdjust(int ny, int nx) {
		int destPlace = grid[ny][nx] - 1;
		int desty = destPlace / 4;
		int destx = destPlace % 4;
		myEstimate += MD(desty,destx,ny,nx);
		myEstimate -= MD(desty,destx,zy,zx);
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

unordered_map<int,vector<State>> memo;

bool okay(State &cur) {
	if (memo.count(cur.hash)) {
		for(auto &x: memo[cur.hash]) 
			if (x.stateEqual(cur)) 
				return false;
	}
	return true;
}

int search(State &cur, int g, int bound, char prevMove) {
	int f = g + cur.myEstimate;
	if (f>bound) return f;
	//if in memo
	/*cur.hash = cur.getHash();
	if (!okay(cur)) return INF;*/
	if (cur.myEstimate==0) {
		for(int i=0;i<g;i++) cout << ans[i];
		cout << endl;
		return FOUND;
	}
	if (g>State::DEPTH_LIMIT) return NOT_FOUND;		
	int min = INF;
	for(int i=0;i<4;i++) {
#ifdef PREV
		if (dir[i]=='U' && prevMove=='D') continue;
		if (dir[i]=='D' && prevMove=='U') continue;
		if (dir[i]=='L' && prevMove=='R') continue;
		if (dir[i]=='R' && prevMove=='L') continue;
#endif
		int ny = cur.zy + dy[i];
		int nx = cur.zx + dx[i];
		
		if (ny<State::ROWS && ny>=0 && nx<State::COLS && nx>=0) {
			cur.adjust(ny,nx);
			
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			swap(cur.zy,ny); swap(cur.zx,nx);

			//get new hash instantly
			ans[g]=dir[i];
			
			int t = search(cur,g+1,bound, dir[i]);
			
			swap(cur.zy,ny); swap(cur.zx,nx);
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);

			cur.undoAdjust(ny,nx);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;
		}
	}
	return min;
}

int IDAstar(State &s) {
	memo.clear();
	int bound = s.estimate();
	while (true) {
		int t = search(s,0,bound,' ');
		//cout << "bound = " << bound << endl;
		if (t==FOUND) return FOUND;
		if (t==INF) return NOT_FOUND;
		bound = t;
	}
}

void initDestination() {
	int val=1;
	for(int i=0;i<State::ROWS;i++) 
		for(int j=0;j<State::COLS;j++) 
			dest.grid[i][j]=val++;

	dest.grid[State::ROWS-1][State::COLS-1] = 0;
	dest.zy=State::ROWS-1; dest.zx=State::COLS-1;
}

int main() {
	initDestination();
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	
	for(int caseNum=1;caseNum<=n;caseNum++) {
		State s;
		for(int i=0;i<State::ROWS;i++) {
			for(int j=0;j<State::COLS;j++){
				cin >> s.grid[i][j];
				if (s.grid[i][j]==0) {
					s.zy=i; s.zx = j;
				}
			} 
		}
		s.hash = s.getHash();
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