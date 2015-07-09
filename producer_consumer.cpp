#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

int itemCount = 0;
const int SIZE = 10;
int printCount = 0;

mutex coutMutex;
condition_variable cond;

bool producerWaitCondition() {
	return itemCount!=SIZE;
}

int producer(void) {
	//make item until full
	while (true) {
		if (itemCount==SIZE) continue;
		unique_lock<mutex>myLock(coutMutex);
		cond.wait(myLock,producerWaitCondition);
		++itemCount;
		++printCount;
		cout << "Producer " << itemCount <<" "<<printCount<< endl;
		myLock.unlock();
		cond.notify_all();
	}
}

bool consumerWaitCondition() {
	return itemCount != 0;
}

int consumer(void) {
	//use item until empty
	while (true) {
		if (itemCount == 0) continue;
		unique_lock<mutex>myLock(coutMutex);
		cond.wait(myLock,consumerWaitCondition);
		--itemCount;
		++printCount;
		cout <<"Consumer "<< itemCount <<" "<<printCount<< endl;
		myLock.unlock();
		cond.notify_all();
	}
}



int main() {
	ios_base::sync_with_stdio(false);
	vector<thread>threads;
	for(int i=0;i<4;i++) {
		threads.push_back(thread(producer));
		threads.push_back(thread(consumer));
	}
	for(auto &x:threads){
		x.join();
	}
	return 0;
}