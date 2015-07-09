#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

static mutex barrier;

 void dot_product(const vector<int> &v1, const vector<int> &v2, int &result, int L, int R) {
 	int localSum=0;
 	for(int i=L;i<R;i++) {
 		localSum += v1[i] * v2[i];
 	}
 	lock_guard<mutex> myLock(barrier);
 	result += localSum;
 }

 vector<int> bounds(int nElements,int nThreads) {
 	vector<int> ans;
 	int leftOver = nElements % nThreads;
 	int elementsPerThread = nElements / nThreads;

 	for(int i=0;i<nThreads;i+=elementsPerThread) {
 		ans.push_back(i);
 	}
 	ans.push_back(nElements);//hack don't need leftover
 	return ans;
 }

 int main() {
 	int nElements = 100000000;
 	int nThreads = 8;
 	int result = 0;
 	//cout << "start " << endl;
 	vector<int> v1(nElements,1), v2(nElements,2);
 	vector<int>limits = bounds(nElements,nThreads);
 	vector<thread>threads;
 	//cout << "after bounds "<< endl;
 	for(int i=0;i<nThreads;i++) {
 		threads.push_back(thread(dot_product,ref(v1),ref(v2),ref(result),limits[i],limits[i+1]));
 	}
 	for(auto &t:threads) t.join();
 	cout << result << endl;
 	return 0;
 }