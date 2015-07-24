#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char,int> number;


int main() {
	int start = 'A';
	for(int start = 'A'; start<='O';start++) {
		int toMap = (start-'A') / 3 + 2;
		number[(char)start] = toMap;
	}
	number['P'] = 7;
	number['Q'] = 7;
	number['R'] = 7;
	number['S'] = 7;

	number['T'] = 8;
	number['U'] = 8;
	number['V'] = 8;

	number['W'] = 9;
	number['X'] = 9;
	number['Y'] = 9;
	number['Z'] = 9;

	string s;
	while (cin >> s) {
		for(auto &x:s) {
			if (number.count(x)) cout << number[x];
			else cout << x;
		}
		cout << endl;
	}

	return 0;
}