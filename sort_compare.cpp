#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void combsort(vector<int>&b) {
	int gap=b.size();
	double shrink = 1.3;
	bool swapped = true;
	
	while (true) {
		if (gap==1 && !swapped)break;
		gap = (int)(gap/shrink);
		if (gap < 1) gap=1;
		
		int i=0;
		swapped=false;
		while (i+gap <= b.size()) {
			swap(b[i],b[i+gap]);
			swapped = true;
			i++;
		}
	}
}
const int SIZE = 10;
int main() {
	int n; 
	vector<int>a;
	for(int i=0;i<SIZE;i++) {
		a.push_back(rand());
	}
	vector<int>b=a;
	int start = clock();
	sort(a.begin(),a.end());
	int end = clock();
	cout << end - start << endl;
	
	start = clock();
	combsort(b);
	for(int i=0;i<b.size();i++) cout << b[i] << endl;
	end = clock();
	cout << end - start;
	return 0;
}
	
