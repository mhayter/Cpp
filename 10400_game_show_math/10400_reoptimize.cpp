//#include "my_fast_io.h"
#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <cstdint>
using namespace std;

//certified #1 but wrong no / check for / zero or integer division
//#1 8/12/2015 0.003s 

char ops[]="+-*/";
int operands[110];
char operators[110];
int nNums;
bool solFound;
int ans;

const int ADD = 32000;

bitset<64010> memo[110];

void findSol(int depth,int val) {
	//if (val > ADD*5 ||  val < -ADD*5) return;
	if (depth == nNums) {
		if (val == ans) {
			for(int i=0;i+1<nNums;++i) {
				cout << operands[i] << operators[i+1];
			}
			cout << operands[nNums-1] << '=' << ans << '\n';
			solFound = true;
		}
		return;
	}

	if (val <=ADD && val>=-ADD) {
		if (memo[depth][val+ADD]) return;
		memo[depth][val+ADD] = 1;
	} else {
		return; 
	}
	//add
	operators[depth] = '+';
	findSol(depth+1,val+operands[depth]);
	if (solFound) return;

	operators[depth] = '-';
	findSol(depth+1,val-operands[depth]);
	if (solFound) return;

	operators[depth] = '*';
	findSol(depth+1,val*operands[depth]);
	if (solFound) return;

	// this is incorrect 2 33 2 16 should be NO EXPRESSION
	// division by zero: 2 0 0 3 
	//if (operands[depth] && val % operands[depth] ==0 ) {
		operators[depth] = '/';
		findSol(depth+1,val/operands[depth]);
		if (solFound) return; // needed?
	//}
}
/*
namespace CodeForcesIO {
static char stdinBuffer[32*1024];
static char* stdinDataEnd = stdinBuffer + sizeof (stdinBuffer);
static const char* stdinPos = stdinDataEnd;

void readAhead(size_t amount)
{
    size_t remaining = stdinDataEnd - stdinPos;
    if (remaining < amount) {
       memmove(stdinBuffer, stdinPos, remaining);
       size_t sz = fread(stdinBuffer + remaining, 1, sizeof (stdinBuffer) - remaining, stdin);
       stdinPos = stdinBuffer;
       stdinDataEnd = stdinBuffer + remaining + sz;
       if (stdinDataEnd != stdinBuffer + sizeof (stdinBuffer))
         *stdinDataEnd = 0;
    }
}

int readInt()
{
    readAhead(16);

    while (*stdinPos <=' ') ++stdinPos;
    int x = 0;
    bool neg = false;
    if (*stdinPos == '-' && *(stdinPos+1)>='0') {
       ++stdinPos;
       neg = true;
    }
    while (*stdinPos >= '0' && *stdinPos <= '9') {
       x *= 10;
       x += *stdinPos - '0';
       ++stdinPos;
    }

    return neg ? -x : x;
}
}
*/
#ifdef ONLINE_JUDGE
int addFactor = 1;
#else
int addFactor = 2;
#endif
int main() {
	//FastInput input;
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n; // '\n'
	cin >> n;
	//if (n>24) return 0; // small testcases <=24
	//cerr << "n= " << n << endl;
	for(int caseNum=1;caseNum<=n;++caseNum) {
		cin >> nNums;
		//nNums = CodeForcesIO::readInt();
		//cerr << "nNums " << nNums << endl;
		for(int i=0;i<nNums;++i) {
			cin >> operands[i];
			//operands[i] = CodeForcesIO::readInt();
			//cerr << "ops " << operands[i] << " ";
			memo[i] = 0;
		}
		//cerr << endl;
		cin >> ans;
		//ans = CodeForcesIO::readInt(); //'\n'
		//cerr <<"ans = " << ans <<endl;
		solFound = false;
		findSol(1,operands[0]);
		if (!solFound) {
			cout <<"NO EXPRESSION\n";
		}
	}
	cout.flush();
	//cout << "heyo\n";
	return 0;
}