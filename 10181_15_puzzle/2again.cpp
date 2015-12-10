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

/*
Right 0.003
*/
//tied #1 (5) 0.000s not as good as true_sol 5/3*hv 
#define PREV

class State {
public:
	State() { 
		myEstimate=zIndex=-1;
	}
	State (const State &rhs) {
		for(int i=0;i<ROWS*COLS;i++) 
			this->grid[i] = rhs.grid[i];
		myEstimate = rhs.myEstimate;
		zIndex = rhs.zIndex;
	}
	State& operator= (State s) {
		swap(grid,s.grid);
		swap(myEstimate,s.myEstimate);
		swap(zIndex,s.zIndex);
		return *this;
	}
	friend bool operator<(const State &lhs, const State &rhs);
	bool stateEqual(const State &rhs) const {
		for(int i=0;i<ROWS*COLS;i++)
			if (grid[i]!= rhs.grid[i] )
					return false;
		return true;
	}

	bool isSolvable() const {
		int a[ROWS*COLS] = {0};
		int k=0;
		int row=1;
		for(int i=0;i<ROWS*COLS;i++) {
			if(this->grid[i]==0)
				row = i / 4+1;	
			a[k++] = this->grid[i];			
		}
		//cout << " row = " << row << endl;
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
	inline int MD (int dy, int dx, int y, int x) const {
		return abs(dy-y) + abs(dx-x);
	}

	//only for initial estimate
	int estimate() {
		int total=0;
		for(int i=0;i<ROWS*COLS;i++) {
			if (this->grid[i]){
				int v= this->grid[i]-1;
				int srow = v/COLS;
				int scol = v%ROWS;
				total+=MD(i/4,i%4,srow,scol);
			}
		}
		return this->myEstimate=total;
	}

	void adjust(int ny,int nx,int desty,int destx) {
		myEstimate += MD(desty,destx,zIndex/4,zIndex%4);
		myEstimate -= MD(desty,destx,ny,nx);
	}
	//change sor no recalc
	void undoAdjust(int ny, int nx,int desty,int destx) {
		myEstimate += MD(desty,destx,ny,nx);
		myEstimate -= MD(desty,destx,zIndex/4,zIndex%4);
	}
	void print() {
		for(int i=0;i<ROWS*COLS;i++) {
			cout << grid[i] << " ";
			if(i%ROWS==0)
				cout << endl;
		}
		cout << endl;
	}
	const static int MOD = 999999937; // BIG PRIME < 1E9
	const static int ROWS = 4;
	const static int COLS = 4;
	const static int DEPTH_LIMIT = 50; //50

	int grid[ROWS*COLS]; 
	int myEstimate;
	int zIndex;
};

bool operator<(const State &lhs, const State &rhs) {
	return lhs.zIndex < rhs.zIndex;
}
State dest;

//absolute estimate 
const int INF = 100;
const int FOUND = 999;
const int NOT_FOUND = -1;

const int dy[] = {1,0, -1, 0};
const int dx[] = {0, 1,0, -1};

const int add[] = {4,1,-4,-1};
const char dir[]="DRUL";
const char idir[]="ULDR";

char ans[100];
int bound;

int search(State &cur, int g, char prevMove) {
	int f = g + 2*cur.myEstimate;
	if (f>bound) return f;
	//if in memo
	if (cur.myEstimate == 0) {
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
		if (dir[i]=='R') {
			if (cur.zIndex%4==3) continue;
		} else if (dir[i]=='L') {
			if (cur.zIndex%4==0) continue;
		}
		int np = cur.zIndex + add[i];
		/// 0.0003s
		int ny = np / 4;
		int nx = np % 4;
		if (ny<State::ROWS && ny>=0 && nx<State::COLS && nx>=0) {
			
			int destPlace = cur.grid[np] - 1;
			int desty = destPlace / 4;
			int destx = destPlace % 4;
				
			cur.adjust(ny,nx,desty,destx);
			swap(cur.grid[np], cur.grid[cur.zIndex]);
			swap(cur.zIndex,np); 
			//get new hash instantly
			ans[g]=dir[i];
			
			int t = search(cur,g+1,dir[i]);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;

			swap(cur.zIndex,np);
			swap(cur.grid[np], cur.grid[cur.zIndex]);
			cur.undoAdjust(ny,nx,desty,destx);
		}
	}
	return min;
}

int IDAstar(State &s) {
	bound = s.estimate();
	while (true) {
		int t = search(s,0,' ');
		//cout << "bound = " << bound << endl;
		if (t==FOUND) return FOUND;
		if (t==INF) return NOT_FOUND;
		bound = t;
	}
}

void initDestination() {
	int val=1;
	for(int i=0;i<State::ROWS * State::COLS;i++) 
		dest.grid[i]=val++;

	dest.grid[15]=0;
	dest.zIndex=15;
}

int main() {
	initDestination();
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	
	for(int caseNum=1;caseNum<=n;caseNum++) {
		State s;
		for(int i=0;i<State::ROWS * State::COLS;i++) {
			cin >> s.grid[i];
			if (s.grid[i]==0)  {
				//cout << "i = " << i << endl;
				s.zIndex=i;
			}
		}

		if (!s.isSolvable()) {
			cout << "This puzzle is not solvable." << endl;
		} else {
			int v = IDAstar(s);
			if (v == NOT_FOUND) {
				throw -1;
				cout << "SHIT This puzzle is not solvable." << endl;
			}
		}
	}
	return 0;
}