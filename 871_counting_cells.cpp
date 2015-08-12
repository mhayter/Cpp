#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string>grid;
bool visited[30][30];

int n,m;
int nFilled = 0;
bool isValid(int y,int x) {
	if (y<0 || x<0 || y>=n || x>=m)return false;
	if (visited[y][x]) return false;
	if (grid[y][x] != '1') return false;
	return true;
}
void fill (int y,int x) {
	if (!isValid(y,x)) return ;
	visited[y][x] = true;
	nFilled++;
	fill(y+1,x+1);
	fill(y+1,x-1);
	fill(y-1,x-1);
	fill(y-1,x+1);
	fill(y+1,x);
	fill(y-1,x);
	fill(y,x+1);
	fill(y,x-1);
}

int floodFill() {
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) {
		visited[i][j] = 0;
	}
	int maxFilled = 0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			//cerr << "i = " << i << " j = " << j << endl;
			if (!visited[i][j]) {
				nFilled = 0;
				fill(i,j);
				maxFilled = max(maxFilled,nFilled);
			}
		}
	}
	return maxFilled;
}

int main() {
	int nCases; cin >> nCases; 
	string line; getline(cin, line);
	getline(cin,line); //blank
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		grid.clear();
		while (getline(cin,line) && isdigit(line[0])) {
			grid.push_back(line);
		}
		n = grid.size();
		m = grid[0].size();

		int ans = floodFill();
		cout << ans << endl;
		if (caseNum != nCases) cout << endl;
	}
	return 0;
}