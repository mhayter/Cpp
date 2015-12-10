
//Adaptation of: LAM PHAN VIET - lamphanviet@gmail.com
//============================================================================
// Author       : LAM PHAN VIET - lamphanviet@gmail.com
// Problem Name : 11195 - Another n-Queen Problem
// Time Limit   : .000s
// Description  : 
//============================================================================

//#2 0.399s

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

int n, res;
int board[maxN];
int specialCase[maxN] = { 0, 1, 2, 3, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596 };

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

int sp=0;
int sta[4*32*maxN];
int *ptr;

void dfs2(int col,int row,int upDiag,int downDiag) {
	ptr = sta;
	*(ptr++) = col;
	*(ptr++) = row;
	*(ptr++) = upDiag;
	*(ptr++) = downDiag;

	int available,lsb;
	const int NminusOne = n-1;

	while (ptr != sta) {
		downDiag = *(--ptr);
		upDiag = *(--ptr);
		row = *(--ptr);
		col = *(--ptr);

		//cout << col << endl;

		//if (col==n) {++res;continue;}
		available = row & board[col] & upDiag & downDiag;
		//if (col == NminusOne) {res+=__builtin_popcount(available); continue;}

		while(available) {
			lsb = available & (-available);

			if (col == NminusOne) {
				++res;
			} else {
				*(ptr++) = col+1;
				*(ptr++) = row^lsb;
				*(ptr++) = ((upDiag^lsb)<<1)|1;
				*(ptr++) = (downDiag^lsb)>>1;
			}

			available &= ~lsb;
		}

	}
}

int main(int argc, char*argv[]) {
	//printf("%s\n",argv[1]);
	char s[maxN];
    int cases = 0;
    while (scanf(" %d ", &n) && n) {
		bool spec = false;
        for (int i = 0; i < n; i++) {
			gets(s);
			board[i] = BIT(n) - 1;
			for (int j = 0; j < n; j++)
				if (s[j] == '*') {
					board[i] ^= BIT(j);
					spec = false;
				}
		}
		allOn = BIT(n-1);
		if (!spec) {
			res = 0;
			if (argc == 1)
				dfs2(0, BIT(n) - 1, BIT(n) - 1, (unsigned) -1);
			else {
				if (strcmp(argv[1],"-b")==0){
					//printf("started backTrack\n");
					backTrack(0, BIT(n) - 1, BIT(n) - 1, (unsigned) -1);
				} else dfs2(0, BIT(n) - 1, BIT(n) - 1, (unsigned) -1);
			}
			//backTrack(0, BIT(n) - 1, BIT(n) - 1, (unsigned) -1);
		}
        else res = specialCase[n];
        printf("Case %d: %d\n", ++cases, res);
    }
    return 0;
}

// Copyright (C) 2012, LamPhanViet