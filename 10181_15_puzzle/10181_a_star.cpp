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
#include <ctime>
using namespace std;
//#define DEBUG

const int ROWS=4;
const int COLS=4;
const int DEPTH_LIMIT = 50; //50

struct State {
	State(){ zx=zy=-1;}
	State (const State &rhs) {
		for(int i=0;i<ROWS;i++) 
			for(int j=0;j<COLS;j++)
				this->grid[i][j] = rhs.grid[i][j];
		zy=rhs.zy;
		zx=rhs.zx;
		path = rhs.path;
	}
	State& operator= (State s) {
		swap(grid,s.grid);
		swap(zy,s.zy);
		swap(zx,s.zx);
		swap(path,s.path);
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
	vector<char>path;
};

char ans[DEPTH_LIMIT];

int MD (int dy, int dx, int y, int x) {
	return abs(dy-y) + abs(dx-x);
}

bool solFound=false;
State s,dest;

bool isSolvable(const State &s) {
	int a[ROWS*COLS] = {0};
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
	return ((inversions+row)%2==0);
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
	return 1.5*total;
}

const int INF = 100;
const int FOUND = 999;
const int NOT_FOUND = -1;

int dy[] = {1,0, -1, 0};
int dx[] = {0, 1,0, -1};
char dir[]="DRUL";
char idir[]="ULDR";
const int MOD = 999999937; // BIG PRIME < 1E9

unordered_map<long long,vector<State>> memo;

long long getValue (const State &s) {
	long long hash=0;
	long long product = 1;
	for(int i=0;i<ROWS;i++) {
		for(int j=0;j<COLS;j++) {
			hash = (hash + s.grid[i][j]*product) % 	MOD;
			product = (product * 31) % MOD;
		}
	}
	return hash;
}
bool okay(State &cur,long long value) {
	if (memo.count(value)) {
		for(auto &x: memo[value]) 
			if (x.stateEqual(cur)) 
				return false;
	}
	return true;
}

int search(State cur, int g, int bound) {
	int f = g + estimate(cur);
	if (f>bound) return f;
	//if in memo
	long long value = getValue(cur);
	if (memo.count(value) && !okay(cur,value)) {
		for(int i=0;i<g;i++)
			cout << ans[i];
		for(auto &x:memo[value]) {
			if (x.stateEqual(s)) {
				for(int i=(int)x.path.size()-1;i>=0;i--) {
					cout << x.path[i];
				}
				cout << endl;
			}
		}
		return FOUND;
	}
	if (g>DEPTH_LIMIT) return NOT_FOUND;		
	int min = INF;
	for(int i=0;i<4;i++) {
		int ny = cur.zy + dy[i];
		int nx = cur.zx + dx[i];
		
		if (ny<ROWS && ny>=0 && nx<COLS && nx>=0) {
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			swap(cur.zy,ny); swap(cur.zx,nx);
			ans[g]=dir[i];
			
			int t = search(cur,g+1,bound);
			
			swap(cur.zy,ny); swap(cur.zx,nx);
			swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
			
			if (t==FOUND) return FOUND;
			if (t<min) min = t;
		}
	}
	return min;
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

int bfs (State &start,int startTime) {
	queue<pair<State,int>>que;
	que.push(make_pair(start,0));
	int nprocessed=0;
	int maxG=-1;
	while (!que.empty()) {
		State temp = que.front().first;
		int g = que.front().second;  que.pop();
		nprocessed++;
		if (g>maxG) cout << (maxG=g) << endl;
		if (g>DEPTH_LIMIT) {return nprocessed;}
		for(int i=0;i<4;i++) {
			int ny = temp.zy + dy[i];
			int nx = temp.zx + dx[i];
			
			if (ny<ROWS && ny>=0 && nx<COLS && nx>=0) {
				
				State cur = temp;
				swap(cur.grid[ny][nx], cur.grid[cur.zy][cur.zx]);
				swap(cur.zy,ny); swap(cur.zx,nx);
				long long value = getValue(cur);

				if (okay(cur,value)) {
					
					cur.path.push_back(idir[i]);
					memo[value].push_back(cur);
					que.push(make_pair(cur,g+1));
				}
			}
		}
	}
}

int main() {
	// your code goes here
	int val=1;
	for(int i=0;i<ROWS;i++) for(int j=0;j<COLS;j++) dest.grid[i][j]=val++;
	dest.grid[ROWS-1][COLS-1] = 0;
	dest.zy=ROWS-1; dest.zx=COLS-1;
	//bfs(dest,clock());
	ios_base::sync_with_stdio(false);
	int n; cin >> n;

	for(int caseNum=1;caseNum<=n;caseNum++) {
		for(int i=0;i<ROWS;i++) for(int j=0;j<COLS;j++){
			cin >> s.grid[i][j];
			if (s.grid[i][j]==0) {
				s.zy=i; s.zx = j;
			}
			
		} 
		solFound=false;
		long long value = getValue(s);
		if (!isSolvable(s)) {
			cout << "This puzzle is not solvable." << endl;
		}else {
			if (memo.count(value)) {
				for(auto &x:memo[value]) {
					if (x.stateEqual(s)) {
						for(int i=(int)x.path.size()-1;i>=0;i--) {
							cout << x.path[i];
						}
						cout << endl;
					}
				}
			} else {
				Astar(s);
			}
		}
	}
	return 0;
}
//http://webdocs.cs.ualberta.ca/~jonathan/PREVIOUS/Courses/657/Notes/10.Single-agentSearch.pdf
//http://www.cprogramdevelop.com/4660352/
