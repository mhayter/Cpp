#include <vector>
#include <iostream>
using namespace std;

void dot_product(const vector<int> &v1, const vector<int> &v2, int &result, int L, int R) {
 	for(int i=L;i<R;i++) {
 		result += v1[i] * v2[i];
 	}
 }

 int main() {
 	int nElements = 100000000;
 	int nThreads = 2;
 	int result = 0;
 	
 	vector<int> v1(nElements,1), v2(nElements,2);
 	dot_product(v1, v2, result, 0, nElements);
 	cout << result << endl;
 	return 0;
 }