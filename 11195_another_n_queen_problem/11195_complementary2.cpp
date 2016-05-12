#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define BIT(n) (1<<(n))
#define AND(a,b) ((a) & (b))
#define OR(a,b) ((a) | (b))
#define XOR(a,b) ((a) ^ (b))
#define sqr(x) ((x) * (x))

#define maxN 20


//uses idea of complementary sets
//if few than or equal 6 cells are unavailable (on their testcases)
//use specialCase - complement = ans rather than excluded cells 

int n, res;
int board[maxN];
//only 19 elements
int specialCase[maxN] = { 0, 1, 2, 3, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184,14772512,95815104,666090624 };

int allOn;

void backTrack(int x, int row, int dia1, int dia2) {
	if (x == n) {
		res++;
		return;
	}
	int avail = row & board[x] & dia1 & dia2;
	//if (x == n-1) {res+=__builtin_popcount(avail); return;}
	while (avail) {
		int y = AND(avail, -avail);
		backTrack(x + 1, row^y, OR(1, (dia1^y) << 1), (dia2^y) >> 1);
		avail &= ~y;
	}
}


void complementaryBackTrack(int x, int row, int dia1, int dia2, int depth) {
	if (depth == n) {
		res++;
		return;
	}
	int avail = row & board[x] & dia1 & dia2;
	//if (x == n-1) {res+=__builtin_popcount(avail); return;}
	while (avail) {
		int y = AND(avail, -avail);
		int next = x+1;
		if (next >= n) next = 0;
		backTrack(next, row^y, OR(1, (dia1^y) << 1), (dia2^y) >> 1);
		avail &= ~y;
	}
}

void printBits (int num) {
	bitset<32> bset(num);
	cerr << bset.to_string() << endl;
}

//DETermine correct colums
vector<int> rowsAvailable;
void dfs(int rowMask, int col,int rightDiag,int leftDiag, int nLeft) {
	if (nLeft <= 0) {++res;return;}
	//updiag [row+col] = true; leftDiag[N+row-col]=true
	//int used = rowUsed| (upDiag)>>(col) | leftDiag>>(N-col) | grid[col];
	//int available = ~used & allOn; // get first N bits
	int row = __builtin_ffs(rowMask) - 1;
	int available = col & ((rightDiag)>>(n-row)) & (leftDiag>>(row)) & board[row];
	//cerr << "row = " << row << endl;
	//printBits(available);
	//return;;

	while(available) {
		//get nex availble bit 
		//int lsb = ((available-1)&available)^available;
		int lsb = available & (-available);
		dfs(rowMask^(1<<row),col^lsb,rightDiag^(lsb<<n-row), leftDiag^(lsb<<row), nLeft-1);

		available &= ~lsb;
	}
}
vector<pair<int,int>> unavailableCells;

int main(int argc, char*argv[]) {
	//printf("%s\n",argv[1]);
	char s[maxN];
    int cases = 0;
    while (scanf(" %d ", &n) && n) {
    	unavailableCells.clear();
		bool spec = true;
        for (int i = 0; i < n; i++) {
			gets(s);
			board[i] = BIT(n) - 1;
			for (int j = 0; j < n; j++)
				if (s[j] == '*') {
					board[i] ^= BIT(j);
					unavailableCells.push_back(make_pair(i,j));
					spec = false;
				}
		}
		allOn = BIT(n)-1;
		if (!spec) {
			res = 0;
			int ans;
			if (unavailableCells.size() > 0 && unavailableCells.size() <=6) {
				//cerr << "entered" << endl;
				//copy board
				int oboard[maxN];
				for(int i= 0;i<n;i++) {
					oboard[i] = board[i];
				}
				int size = unavailableCells.size();
				for(int i=1;i<(1<<size);++i) {
					//may be able to speed up
					for(int k= 0;k<n;k++) 
						board[k] = oboard[k];

					int y = 0;
					int colmask = 0;
					int rightDiag = 0x7fffffff;
					int leftDiag = 0x7fffffff;
					int conflictStart = -1;

					int rowMask = allOn;
					for(int j=0;(1<<j)<=i;++j) {
						if (i & (1<<j) ) {
							//take j 
							//place queen at location
							//what happens if they conflict
							int row = unavailableCells[j].first;
							int col = unavailableCells[j].second;
							//cerr << "row " << row << " col " << col << endl;

							//check for conflict
							if ( (y & (1 << col)) ||
								 (rowMask & (1<<row)) == 0 ||
								 (colmask & (BIT(col))) ||
								 !(leftDiag & (1<<(col+row))) ||
								 !(rightDiag & (1<<(n+col-row))) ){
								//conflict
								//unroll
								//cerr << "conflict!\n";
								conflictStart = j;
								break;
							}
							rowMask &= ~(1<<row);
							y |= (1<< col);
							board[row] ^= BIT(col); colmask|=BIT(col);
							rightDiag^=(1<<(n+col-row));
							leftDiag^=(1<<(col+row));
						}

					}
					if (conflictStart!=-1) {
						//there was a conflict
						continue;
					}
					int col = allOn^y;
					/*cerr << "Calling dfs " << __builtin_ffs(col)-1 << " " <<col<<" " << rightDiag<<" " << leftDiag<<endl;
					bitset<32> colb(col); cerr << colb.to_string() << endl;
					bitset<32> updiagb(rightDiag); cerr << updiagb.to_string() << endl;
					bitset<32> downdiagb(leftDiag); cerr << downdiagb.to_string() << endl;
					*/
					dfs(rowMask,  col, rightDiag, leftDiag,__builtin_popcount(col));
					//cerr << "res = " << res << endl;
				}
				//printf("specialCase = %d res = %d\n",specialCase[n], res);
				ans = specialCase[n] - res;
			} else {
				//cerr << "BT" << endl;
				backTrack(0, BIT(n) - 1, BIT(n) - 1, (unsigned) -1);
				ans = res;
			}
			printf("Case %d: %d\n", ++cases, ans);
			//if (cases >=1) break;
		}
        else 
        	printf("Case %d: %d\n", ++cases, specialCase[n]);
    }
    return 0;
}