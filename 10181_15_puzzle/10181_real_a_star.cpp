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



class State {
public:
	State() { 
		zx=zy=index=hash=-1;
	}
	State (const State &rhs) {
		for(int i=0;i<ROWS;i++) 
			for(int j=0;j<COLS;j++)
				this->grid[i][j] = rhs.grid[i][j];
		zy=rhs.zy;
		zx=rhs.zx;
		index = rhs.index;
		hash = rhs.hash;
	}
	State& operator= (State s) {
		swap(grid,s.grid);
		swap(zy,s.zy);
		swap(zx,s.zx);
		swap(index,s.index);
		swap(hash,s.hash);
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
	int estimate() const {
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
		return total;
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
};

bool operator<(const State &lhs, const State &rhs) {
	return lhs.zy < rhs.zy;
}
State dest;

//TODO: approx estimate?

//absolute estimate 
const int INF = 100;
const int FOUND = 999;
const int NOT_FOUND = -1;

const int dy[] = {1,0, -1, 0};
const int dx[] = {0, 1,0, -1};
const char dir[]="DRUL";
const char idir[]="ULDR";

struct MyTuple {
	int f; int g;
	State s;
	MyTuple(int a, int b, State c) : f(a), g(b), s(c)
	{}
	friend bool operator<(const MyTuple &lhs, const MyTuple &rhs);
};

bool operator<(const MyTuple &lhs, const MyTuple &rhs) {
	if (lhs.f < rhs.f) return true;
	if (lhs.f == rhs.f) {
		if (lhs.g>rhs.g) return true;
	}
	return false;
}

unordered_map<long long,vector<State>> memo;
set<MyTuple>que;
unordered_map<int,int>parent;
unordered_map<int,char>parentMove;

bool okay(State &cur) {
	if (memo.count(cur.hash)) {
		for(auto &x: memo[cur.hash]) 
			if (x.stateEqual(cur)) 
				return false;
	}
	return true;
}

void reconstruct_path(int index) {
	if (index==-1) return;
	reconstruct_path(parent[index]);
	cout << parentMove[index]; 
}

int bfs (State &start) {
	memo.clear();
	parent.clear();
	parentMove.clear();
	int parentIndex = 0;

	queue< pair<int,State> > que;
	que.push(make_pair(0,start));
	while (!que.empty()) {
		int g = que.front().first;
		State cur = que.front().second;
		que.pop();

		cout << " g= " << g << endl;
		cur.print();

		if (g>State::DEPTH_LIMIT) continue;
		if (cur.stateEqual(dest) ) {
			reconstruct_path(cur.index);
			cout << endl;
			return FOUND;
		}
		memo[cur.hash].push_back(cur);

		for(int i=0;i<4;i++) {
			int ny = cur.zy + dy[i];
			int nx = cur.zx + dx[i];

			if (ny>=4 || ny<0 || nx>=4 || nx <0) continue;
			cout << g << " " << dir[i] << endl;
			State newState = cur;
			newState.zy = ny;
			newState.zx = nx;
			swap(newState.grid[ny][nx],newState.grid[cur.zy][cur.zx]);
			newState.hash = newState.getHash();
			
			if (!okay(newState)) continue;
			if (g + newState.estimate() >State::DEPTH_LIMIT) continue;
			cout << "okay" << endl;
			
			parent[parentIndex] = cur.index;
			parentMove[parentIndex] = dir[i];

			newState.index = parentIndex++;
			int newg = g+1;
			que.push(make_pair(newg,newState));
		}
	}
	return NOT_FOUND;
}

int Astar (State &start) {
	memo.clear();
	que.clear();
	parent.clear();
	parentMove.clear();

	int parentIndex=0;
	que.insert(MyTuple(start.estimate(),0,start));
	//cout <<"Start" << endl;
	while (!que.empty()) { //open set not empty

		int f = que.begin()->f;
		int g = que.begin()->g;  
		State temp = que.begin()->s; //current with lowest f score
		
		cout << "f = " << f << " g= " << g << endl;
		temp.print();

		que.erase(que.begin());// remove current rom openset
		if (g>State::DEPTH_LIMIT) {continue;}

		if (temp.stateEqual(dest)) {
			cout << g << endl;
			reconstruct_path(temp.index);
			cout << endl;
			return FOUND;
		}
		if (g==10) cout << "f = " << f << endl;
		//if (f > State::DEPTH_LIMIT) continue;
		memo[temp.hash].push_back(temp); //add current to closed set
	
		for(int i=0;i<4;i++) { // for each neighbor
			int ny = temp.zy + dy[i];
			int nx = temp.zx + dx[i];
			
			if (ny<State::ROWS && ny>=0 && nx<State::COLS && nx>=0) {
				
				State cur = temp;
				swap(cur.grid[ny][nx], cur.grid[temp.zy][temp.zx]);
				cur.zy = ny;
				cur.zx = nx;
				cur.hash = cur.getHash();

				int newh = cur.estimate(); 
				/*
				calc in constant time based on direction
				*/
				int newg = g+1; // tentative g score
				int newf = newg+newh; // fscore

				//if (!okay(cur)) continue; // if in cloased set continue
				//if (newf > State::DEPTH_LIMIT) continue;
				parent[parentIndex] = temp.index;
				parentMove[parentIndex] = dir[i];

				cur.index = parentIndex++;		

				que.insert(MyTuple(newf,newg,cur));
			}
		}
	}
	//throw -1;
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
			int v = Astar(s);
			if (v == NOT_FOUND) {
				cout << "SHIT This puzzle is not solvable." << endl;
				cout << parent.size() << endl;
			}
		}
	}
	return 0;
}
//http://webdocs.cs.ualberta.ca/~jonathan/PREVIOUS/Courses/657/Notes/10.Single-agentSearch.pdf
//http://www.cprogramdevelop.com/4660352/
