#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <cctype>
#include <queue>
#include <bitset>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
//#define DEBUG

const int ROWS=3;
const int COLS=3;
const int DEPTH_LIMIT = 33;

struct State {
	State(){ zx=zy=-1;}
	State (const State &rhs) {
		for(int i=0;i<ROWS;i++) 
			for(int j=0;j<COLS;j++)
				this->grid[i][j] = rhs.grid[i][j];
		zy=rhs.zy;
		zx=rhs.zx;
	}
	State& operator= (State s) {
		swap(grid,s.grid);
		return *this;
	}
	bool stateEqual(const State &rhs) {
		for(int i=0;i<ROWS;i++)
			for(int j=0;j<COLS;j++) 
				if (grid[i][j] != rhs.grid[i][j] )
					return false;
		return true;
	}
	int grid[ROWS][COLS]; 
	int zy,zx;
};

char ans[DEPTH_LIMIT];

int MD (int dy, int dx, int y, int x) {
	return abs(dy-y) + abs(dx-x);
}

bool solFound=false;
State s,dest;

bool isSolvable() {
	int a[10] = {0};
	int k=0;
	int row=1;
	for(int i=0;i<ROWS;i++) 
		for(int j=0;j<COLS;j++) {
			if(s.grid[i][j])
				a[k++] = s.grid[i][j];
			else row=i+1;
		}
	//for(int i=0;i<8;i++) cout << a[i] << " ";
	//cout <<endl;
	int inversions=0;
	for(int i=0;i<k;i++) {
		for(int j=i+1;j<k;j++) {
			if (a[i]>a[j]) inversions++;
		}
	}
	return ((inversions)%2==0);
}

int estimate(State &init) {
	int total=0;
	for(int i=0;i<ROWS;i++) {
		for(int j=0;j<COLS;j++) {
			if (init.grid[i][j]){
				int v= init.grid[i][j]-1;
				int srow = v/COLS;
				int scol = v%ROWS;
				total+=MD(i,j,srow,scol);
			}
		}
	}
	return total;
}

const int INF = 100;
const int FOUND = 999;
const int NOT_FOUND = -1;

int dy[] = {1,0, -1, 0};
int dx[] = {0, 1,0, -1};
char dir[]="DRUL";

int search(State cur, int g, int bound) {
	int f = g + estimate(cur);
	if (f>bound) return f;
	if (cur.stateEqual(dest)) {
		for(int i=0;i+1<g;i++)
			cout << (char)tolower(ans[i]);
		if (g>0) cout << (char) tolower(ans[g-1]) << endl;
		return FOUND;
	}
	//if (g>DEPTH_LIMIT) return NOT_FOUND;
			
	int min = INF;
	for(int i=0;i<4;i++) {
		int ny = cur.zy + dy[i];
		int nx = cur.zx + dx[i];
		
		if (ny<ROWS && ny>=0 && nx<COLS && nx>=0) {
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			swap(cur.zy,ny); swap(cur.zx,nx);
		+	ans[g]=dir[i];
			
			int t = search(cur,g+1,bound);
			
			swap(cur.zy,ny); swap(cur.zx,nx);
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;
		}
	}
	return min;2
}

int Astar(State &init) {
	int bound = estimate(init);
	while (true) {
		int t = search(init,0,bound);
		if (t==FOUND) return FOUND;
		if (t==INF) return NOT_FOUND;
		bound = t;
	}
}

int main() {
	// your code goes here
	int val=1;
	for(int i=0;i<ROWS;i++) for(int j=0;j<COLS;j++) dest.grid[i][j]=val++;
	dest.grid[ROWS-1][COLS-1] = 0;
	
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	 
	for(int caseNum=1;caseNum<=n;caseNum++) {
		for(int i=0;i<ROWS;i++) for(int j=0;j<COLS;j++){
			char c; cin>>c;
			if (c=='x') {
				s.zy=i;s.zx=j;
				s.grid[i][j]=0;
			} else
				s.grid[i][j]= c-'0';
			
		} 
		solFound=false;
		if (!isSolvable()) {
			cout << "unsolvable" << endl;
		}else {
			int v = Astar(s);
		}
		if (caseNum!=n) cout<<endl;
	}
	return 0;
}
//http://webdocs.cs.ualberta.ca/~jonathan/PREVIOUS/Courses/657/Notes/10.Single-agentSearch.pdf
//http://www.cprogramdevelop.com/4660352/
