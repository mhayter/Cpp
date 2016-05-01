#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

const int NROWS = 9;
const int NCOLS = 9;

const int UNASSIGNED = 0;

bool solved;

// zero will be unassigned

int grid[NROWS][NCOLS];

void solve();
void printSolution();
void printGrid();

int unassignedCellsPlace;
vector<pair<int,int>>unassignedCells;

int n;


int main() {
	cin >> n;
	while (true) {
		//cerr << "n = " << n << endl;
		unassignedCells.clear();
		unassignedCellsPlace = 0;
		solved = false;
	
		//convert to grid
		int sPlace = 0;
		for(int i=0;i<n*n;++i) {
			for(int j=0;j<n*n;j++) {

				cin >> grid[i][j];
				if (grid[i][j]==UNASSIGNED) {
					unassignedCells.push_back(make_pair(i,j));
				}
			}
		}
		//cerr << "Grid\n";
		//printGrid();
		solve();
		printSolution();
		//cin >> n;
		//cerr << "n = " << n << endl;
		if (cin >> n) cout << "\n";
		else break;
	}
	return 0;
}

void printSolution() {
	if (solved)
		printGrid();
	else 
		cout << "NO SOLUTION\n";
}

bool findLocation(int &row,int &col) {
	if (unassignedCellsPlace < unassignedCells.size()) {
		row = unassignedCells[unassignedCellsPlace].first;
		col = unassignedCells[unassignedCellsPlace].second;
		unassignedCellsPlace++;
		return true;
	}
	return false;
}

//assumes 1- ROWS as index
bool colValid(int col, int num) {
	//only one in column
	for(int row=0;row<n*n;row++) {
		if (grid[row][col] == num) return false;
	}
	return true;
}

bool rowValid(int row, int num) {
	for(int col=0;col<n*n;col++) {
		if (grid[row][col] == num) return false;
	}
	return true;
}

//assums 1-9
bool squareValid(int row,int col, int num) {
	//where does it belong?
	//only one
	int rowStart = (row/n) * n; // either 0 3 6
	int colStart = (col/n) * n; // eigher 0 3 6
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			int value = grid[rowStart+i][colStart+j];
			if (value == num) return false;
		}
	}
	return true;
}

bool isValid(int row, int col, int num) {
	return 
		colValid(col,num) && 
		rowValid(row,num) && 
		squareValid(row,col,num);
}

void printGrid() {
	for(int i=0;i<n*n;i++) {
		for(int j=0;j<n*n;j++) {
			cout << grid[i][j];
			if (j<(n*n-1))
				cout << " ";
		}
		cout << "\n";
	}
	//cout << "Done";
	//cout << "\n";
}

void solve() {
	//if not solved
	int row, col;
	if (!solved) {
		//find acceptable location
		solved = !findLocation(row,col);
		if (solved) {
			//printSolution();
			return;
		}
	}else return;
	//find new location (min - max)
	for(int num = 1; num <= n*n; num++) {
		//cerr << "trying num " << num << endl;
		if (isValid(row,col,num)) {
			grid[row][col] = num;
			solve();
			if (solved)return;
			grid[row][col] = UNASSIGNED;
		}
	}
	unassignedCellsPlace--;
}