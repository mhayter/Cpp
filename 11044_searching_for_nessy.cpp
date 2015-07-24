#include <iostream>
#include  <cmath>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	while (nCases--) {
		int rows, cols; cin >> rows >> cols;
		rows-=2; cols-=2;

		int r = ceil(rows / 3.);
		int c = ceil(cols / 3.);

		int ans = r * c;
		cout << ans << endl;
	}
	return 0;
}