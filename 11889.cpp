#include <iostream>
#include <algorithm>
using namespace std;

//wrong

int main() {
	int nCases; cin >> nCases;
	while (nCases--) {
		int a, b; cin >> a >> b;
		//if (a > b) swap(a,b);
		if (b % a == 0) cout << b/a << "\n";
		else cout << "NO SOLUTION\n";
	}
	return 0;
}