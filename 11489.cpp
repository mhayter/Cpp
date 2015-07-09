#include <iostream>
#include <string>
using namespace std;

int getMultiples(int &sum, string &num) {
	int tot = 0;
	for(auto &x:num) {
		if (x%3==0) ++tot;
	}
	return tot;
}

bool makesMultiple(int sum, string &num) {
	for(auto &x:num) {
		if ((sum-(x-'0'))%3==0) return true;
	}
	return false;
}

int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	int T; cin >> T;
	for(int caseNum=1;caseNum<=T;++caseNum) {
		string num; cin >> num;
		int sum=0;
		for(auto &a:num) sum+= a - '0';
		cout << "Case " << caseNum << ": ";
		if (sum % 3 !=0) {
			if (makesMultiple(sum,num)) {//S went
				if (getMultiples(sum,num)%2==1) { // T went
					cout << "T";
				} else cout << "S";
			} else  cout << "T";
		}else { // is mod 3
			if (getMultiples(sum,num)%2==0) cout << "T";
			else cout << "S";
		}
		cout << "\n";
	}
	return 0;
}