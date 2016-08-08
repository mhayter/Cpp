#include <iostream>
#include <unordered_map>
#include <deque>
#include <list>

using namespace std;

//76ms learned what splice was
//80ms reuse find iterator
//92ms list.size bad?
class LRUCache {
public:
	LRUCache(int capacity)
	{
		this->capacity = capacity;	
		this->myQueueSize = 0;
	}
	int get(int key) {
		auto findIterator = myMap.find(key);
		if (findIterator != myMap.end() && findIterator->second.second) {
			//Bubble;
			auto newFront (*(findIterator->second.first));
			myQueue.erase(findIterator->second.first); // just need to move to front not erase
			myQueue.push_front(newFront);
			findIterator->second.first = myQueue.begin();
			return newFront.second;
		}
		return -1;
	}
	void set(int key, int value) {
		if (myQueueSize == capacity) {
			auto findIterator = myMap.find(key);
			if (!(findIterator != myMap.end() && findIterator->second.second)){ // if not in Q
				auto victim = move(myQueue.back());
				myQueue.pop_back(); //don't need to erase just move pointers
				myMap[victim.first].second = false;// could actually remove if wanted
				doFront(key,value);
			} else {
				//auto victim = findIterator->second.first;
				//myQueue.erase(victim);
				myQueue.splice(myQueue.begin(), myQueue, findIterator->second.first);
				myQueue.begin()->second = value;
				findIterator->second.first = myQueue.begin();
			}
		} else {
			auto findIterator = myMap.find(key);
			if (findIterator != myMap.end() && findIterator->second.second){// in Q
				//auto victim = findIterator->second.first;
				//myQueue.erase(victim);
				myQueue.splice(myQueue.begin(), myQueue, findIterator->second.first);
				myQueue.begin()->second = value;
				findIterator->second.first = myQueue.begin();
			} else {
				++myQueueSize;
				doFront(key,value);
			}
		}
		//doFront(key,value);
	}
	void doFront(int key, int value) {
		myQueue.push_front(make_pair(key,value));
		myMap[key] = make_pair(myQueue.begin(), true);
	}
	void printCache() {
		cout << "Printing cache" << endl;
		for(auto &x: myQueue) {
			cout << x.first << " " << x.second << ", ";
		}
	}
private:
	unordered_map<int, pair<list<pair<int,int>>::iterator,bool>> myMap;
	list<pair<int,int>> myQueue;
	int capacity;
	int myQueueSize;
};

int main() {
	{
		LRUCache cache(1);
		cache.set(2,1); //{2:1}
		cout << cache.get(2) << endl;//{2:1} 1
		cache.set(3,2);//{3:2}
		cout << cache.get(2) << endl;//{3:2} -1
		cout << cache.get(3) << endl;//{3:2} 2
	}
	{
		LRUCache cache(2);
		cout << cache.get(2) << endl; // {} -1
		cache.set(2,6); // {2:6} 
		cout << cache.get(1) << endl; // {2:6} -1
		cache.set(1,5); // {1:5, 2:6} 
		cache.set(1,2); // {1:2, 2:6}
		cout << cache.get(1) << endl; //{1:2,2:6} 2
		cout << cache.get(2) << endl; //{2:6,1:2} 6
		cache.set(4,7); // {4:7, 2:6}
		cout << cache.get(1) << endl; //{4:7, 2:6} -1
		cout << cache.get(4) << endl; //{4:7, 2:6} 7
	}
	{
		cout << "Enter cap" << endl;
		int cap;
		cin >> cap;
		LRUCache cache(cap);
		cout << "Enter s or g" << endl;
		char command;
		while (cin >> command) {
			if (command == 's') {
				int key, value; cin >> key >> value;
				cache.set(key,value);
			} else {
				int key; cin >> key;
				cout << cache.get(key) << endl;
			}
			cache.printCache();
		}
	}

	return 0;	
}
