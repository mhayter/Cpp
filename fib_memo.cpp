#include <bits/stdc++.h>
using namespace std;

int memo[100];

int fibMemo(int n) {
	if(n<=1) return 1;
	if (memo[n] !=-1) return memo[n];
	return memo[n] = fibMemo(n-1) + fibMemo(n-2);
}

int fib(int n) {
	if (n<=1) return 1;
	return fib(n-1) + fib(n-2);
}

int main() {
	memset(memo,-1,sizeof(memo)); //1 1 2 3 5 8
	cout << fibMemo(40) << endl;
	return 0;
}