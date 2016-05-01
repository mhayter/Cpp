#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

//set as heap 0.010s 
//myheap 0.000s 4/30/2016


int main() {
	ios_base::sync_with_stdio(false);
	int n; 
	while (true) {
		cin >> n; 
		if (n == 0) break;
		multiset<int> mySet;
		for(int i=0;i<n;i++) {
			int num;
			cin >> num;
			mySet.insert(num);
		}
		//build heap
		//cout << "mySet.size() " << mySet.size() << endl;
		int sum = 0;
		while (mySet.size() >= 2) {
			int num1 = *mySet.begin();
			mySet.erase(mySet.begin());

			int num2 = *mySet.begin();
			mySet.erase(mySet.begin());
			//cout << num1 << " " << num2 << endl;

			int curSum = num1+num2;
			sum += curSum;
			mySet.insert(curSum);
			//cout << "mySet.size() " << mySet.size() << endl;
		}
		cout << sum << "\n";
	}
	return 0;
}