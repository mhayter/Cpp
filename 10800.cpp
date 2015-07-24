#include <iostream>
#include <string>
#include <cstring>
using namespace std;

char grid[60][60];

void printGraph(int maxHeight, const string &s)  {
	for(int i=0;i<maxHeight;i++) {
		int ind = -1;
		for(int j= 2 +(int)s.size() -1; j>=0; j--) {
			if (grid[i][j] != ' ') {
				ind = j+1;
				break;
			}
		}
		//grid[i][ind]='\n'; // guaranteed to be at least |
		for(int j=0;j<ind;j++) 
			cout << grid[i][j];
		cout <<"\n";
	}
	cout << "+-";
	for(int i=0;i<(s.size()+1);i++) cout <<"-";
	cout << "\n";
}

void createGraph(int maxHeight, int start,const string &s) {
	for(int i=0;i<maxHeight;i++) grid[i][0] = '|';

	int curRow = start; // changes if weird negative
	int curCol = 2;
	
	for(int i=0;i<s.size();i++) {
		if (s[i]=='R') {
			grid[curRow][curCol] = '/';
			if (i+1 < s.size() && s[i+1] != 'F') --curRow;
		} else if (s[i] == 'C') {
			grid[curRow][curCol] = '_';
			if (i+1 < s.size() && s[i+1] == 'F') ++curRow;
		} else {
			grid[curRow][curCol] = '\\';
			if (i+1 <s.size() && s[i+1] == 'F') ++curRow;
		}
		curCol++;
	}
}

void getHeights(int &maxHeight, int &minHeight,const string &s) {
	int height = maxHeight = minHeight = 0;
	for (int i=0;i<s.size();i++) { 
		if (s[i]=='R') {
			if (i+1 < s.size() && s[i+1] != 'F') ++height;
		} else if (s[i] == 'C') {
			if (i+1 < s.size() && s[i+1] == 'F') height--;
		} else {
			if (i+1 <s.size() && s[i+1] == 'F') --height;
		}
		maxHeight = max(maxHeight, height);
		minHeight = min(minHeight, height);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int nCases; cin >>nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		memset(grid,' ',sizeof(grid));
		string s; cin >> s;
		//build graph
		
		int maxHeight, minHeight;
		getHeights(maxHeight,minHeight,s);
		
		cout << "Case #" << caseNum << ":\n";
		int graphHeight = (maxHeight - minHeight)+1;

		createGraph(graphHeight, graphHeight+minHeight-1,s);
		printGraph(graphHeight,s);
		cout <<"\n";
	}
	return 0;
}