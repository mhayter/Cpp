#include <bits/stdc++.h>
using namespace std;

const int MAX_SUM = 20010;
//bitset<MAX_SUM>myMap;
unordered_set<int>myMap;
const int SIZE = 110;
int a[SIZE];
int n;

bool isB2() {
	for(int i=0;i<n;i++) {
		int num1 = a[i];
		for(int j=i;j<n;j++) {
			int sum = num1+a[j];

			if (myMap.count(sum)) {
				return false;
			}
			myMap.insert(sum);
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false); 
	int caseNum = 1;
	while (cin >>n){
		bool isValid = true;
		for(int i=0;i<n;i++) {
			cin >> a[i];
			if (a[i] < 1) isValid = false;
			if (i>0) {
				if (a[i]<a[i-1]) {
					isValid = false;
				}
			}
		}
		myMap.clear();

		cout << "Case #"<<caseNum++<<": ";
		if (isValid && isB2()) {
			cout << "It is a B2-Sequence.\n\n";
		} else {
			cout << "It is not a B2-Sequence.\n\n";
		}
		
	}
	return 0;
}