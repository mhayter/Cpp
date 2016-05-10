#include <bits/stdc++.h>
using namespace std;
//added reduce k operation and works!
//still wrong need to reduces stack depth

typedef unsigned long long ull;

unordered_map<ull, ull> myMap;

ull nCr(int n, int k) {
	if (n == k) return 1;
	if (k <= 0) return 1;
	if (k == 1) return n;
	if (k == 2) return (0ull + n)*(n-1)/2;
	ull hash = 1267*n + k;
	if (myMap.count(hash)) return myMap[hash];

	return myMap[hash] = nCr(n-1,k) + nCr(n-1,k-1);
}

int main() {
	int n, k; 
	ios_base::sync_with_stdio(false);
	while (true) {
		cin >> n >> k;
		if (n==0 && k==0) break;

		//create small k
		int newk = n-k;
		if (newk < k) k = newk;
		cout << nCr(n,k) << "\n";
	}
	return 0;
}