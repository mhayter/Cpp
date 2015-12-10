#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <condition_variable>
using namespace std;

int SIZE = 100000;

char str[10];

void singleThreaded() {
	for(int i=0;i<SIZE;i++) {
		if (i%3==0 && i%5==0) {
			cout << "FizzBuzz\n";
		} else if (i%3==0) {
			cout << "Fizz\n";
		} else if (i%5==0){
			cout << "Buzz\n";
		} else {
			cout << i << '\n';
		}
	}
}

void multiThreaded() {
	#pragma omg parallel for
	for(int i=0;i<SIZE;i++) {
		if (i%3==0 && i%5==0) {
			cout << "FizzBuzz\n";
		} else if (i%3==0) {
			cout << "Fizz\n";
		} else if (i%5==0){
			cout << "Buzz\n";
		} else {
			cout << i << '\n';
		}
	}
}

vector<int> bounds(int nElements,int nThreads) {
 	vector<int> ans;
 	int leftOver = nElements % nThreads;
 	int elementsPerThread = nElements / nThreads;
 	//cerr << "nThreads = "<< nThreads << endl;
 	for(int i=0,place=0;i<nThreads;place+=elementsPerThread,i++) {
 		//cerr << "i = " << i <<" " << place<< endl;
 		ans.push_back(place);
 	}
 	ans.push_back(nElements);//hack don't need leftover
 	return ans;
 }

mutex myMutex;
char myArray[1000010][10];
void doIt(int start,int end) {
	for(int i=start;i<end;++i) {
		if (i%3==0 && i%5==0) {
			strcpy(myArray[i],"FizzBuzz\n");
		} else if (i%3==0) {
			strcpy(myArray[i],"Fizz\n");
		} else if (i%5==0){
			strcpy(myArray[i],"Buzz\n");
		} else {
			sprintf(myArray[i],"%d\n",i);
		}
	}
	//lock_guard<mutex> myLock(myMutex);
	//cerr << "Doit Done" << endl;
}

void myMultithreaded(int nThreads=4) {
	vector<thread> threads;
	vector<int> limits = bounds(SIZE, nThreads);

	cerr << "started\n";
	for(int i=0;i<nThreads;i++) { 
		{
			//lock_guard<mutex> myLock(myMutex);
			//cerr << limits[i] << " " << limits[i+1] << endl;
		}
 		threads.push_back(thread(doIt,limits[i],limits[i+1]));
 	}
 	cerr << "here it is\n";
 	for(auto &t:threads) t.join();

 	cerr << "output\n";
 	fwrite(myArray,1, sizeof(myArray), stdout);
 	/*
 	for(int i=0;i<SIZE;++i) {
 		//puts(myArray[i]);
 		cout << myArray[i] << '\n';
 	}
 	*/
 }

int main(int argc,char *argv[]) {

	ios_base::sync_with_stdio(false);
	if (argc<3) return -1;
	for(int i=0;i<argc;++i) {
		cerr << argv[i] << endl;
	}
	SIZE = atoi(argv[1]);
	if (strcmp(argv[2], "-m") == 0){
		cerr << "multiThreaded\n";
		multiThreaded();
	} else if (strcmp(argv[2],"-s") == 0){
		cerr << "singleThreaded\n";
		singleThreaded();
	} else {
		cerr << "My multiThreaded\n";
		myMultithreaded(4);
	}
	return 0;
}