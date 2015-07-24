#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <cctype>
#include <vector>
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

int MD (int dy, int dx, int x, int y) {
	return abs(dy-y) + abs(dx-x);
}

bool solFound=false;
State s,dest;
int limit;

long long getValue() {
	long long place = 1;
	long long tot = 0;
	for (int i=0;i<ROWS;i++) {
		for(int j=0;j<COLS;j++) {
			tot += (place * (s.grid[i][j]+1));
			place*=31;
			tot%=1000000007;
			place%=1000000007;
		}
	}
	return tot;
}
vector<int> getVector() {
	vector<int> vec;
	for(int i=0;i<ROWS;i++) {
		for(int j=0;j<COLS;j++) {
			vec.push_back(s.grid[i][j]);
		}
	}
	return vec;
}
unordered_map<long long, bool>visited;
//map<vector<int>,bool> visited;

void dfs(int depth) {
	#ifdef DEBUG
	cout << "depth " << depth << endl;
	for(int i=0;i<depth;i++) cout << ans[i];
			cout << endl;
	for(int i=0;i<ROWS;i++) {
				for (int j=0;j<COLS;j++) {
					cout << s.grid[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
	#endif

	if (s.stateEqual(dest)) {
		solFound = true;
		for(int i=0;i+1<depth;i++) {
			cout <<(char) tolower(ans[i]);
		}
		if (depth>0)
			cout << (char)tolower(ans[depth-1]) << endl;
		return;
	}
	if (depth==limit) 
		return;
	if (solFound) return;
	/*vector<int>v=getVector();
	if (visited.count(v)) return;
	visited[v]=true;
	*/
	long long value = getValue();
	if (visited.count(value)) return;
	visited[value] = true;
	
	if (s.zx+1<COLS) {
		//cout << "right" << endl;
		ans[depth] = 'R';
		swap(s.grid[s.zy][s.zx+1], s.grid[s.zy][s.zx]);
		s.zx++;
		dfs(depth+1);
		s.zx--;
		swap(s.grid[s.zy][s.zx+1], s.grid[s.zy][s.zx]);
	}
	//left
	if (s.zx-1>=0) {
		//cout << "left" << endl;
		ans[depth] = 'L';
		swap(s.grid[s.zy][s.zx-1], s.grid[s.zy][s.zx]);
		s.zx--;
		dfs(depth+1);
		s.zx++;
		swap(s.grid[s.zy][s.zx-1], s.grid[s.zy][s.zx]);
	}
	//down
	if (s.zy+1<ROWS){
		//cout << "down" << endl;
		ans[depth] = 'D';
		swap(s.grid[s.zy+1][s.zx], s.grid[s.zy][s.zx]);
		s.zy++;
		dfs(depth+1);
		s.zy--;
		swap(s.grid[s.zy+1][s.zx], s.grid[s.zy][s.zx]);
	}
	//up
	if (s.zy-1>=0) {
		//cout << "up" << endl;
		ans[depth] = 'U';
		swap(s.grid[s.zy-1][s.zx], s.grid[s.zy][s.zx]);
		s.zy--;
		dfs(depth+1);
		s.zy++;
		swap(s.grid[s.zy-1][s.zx], s.grid[s.zy][s.zx]);
	}	
}

void Astar(State &init) {
	for(int i=0;i<DEPTH_LIMIT;i++) {
		limit = i;
		//cout << "NEW LIMIT "  << i << endl;
		visited.clear();
		dfs(0);
		if (solFound) break;
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
		Astar(s);
		if (!solFound) {
			cout << "unsolvable" << endl;
		}
		if (caseNum+1!=n) cout<<endl;
	}
	return 0;
}
