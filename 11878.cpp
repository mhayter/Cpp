#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
	string s; 
	int cnt = 0;
	while (cin >> s) {
		stringstream ss(s);
		int num1; char op; int num2; char eq; int ans;
		ss >> num1 >> op >> num2 >> eq >> ans;

		if (op == '+') {
			if (num1+num2 == ans) cnt++;
		} else {
			if (num1-num2 == ans) cnt++;
		}
	}
	cout << cnt << endl;
	return 0;
}