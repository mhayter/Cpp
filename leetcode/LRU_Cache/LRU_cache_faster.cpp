#include <iostream>
#include <unordered_map>
#include <deque>
#include <list>

using namespace std;

//64ms was memory limit exceeded

//76ms added splice to get, no diff
//76ms learned what splice was
//80ms reuse find iterator
//92ms list.size bad?

namespace HashTable {

	struct Node {
		int count;
		int value;
		list<pair<int,int>>::iterator lpiiIterator; 
	};
	const int MOST_UNIQUE_HASHES = 1010*10;
	unsigned clearHashes[MOST_UNIQUE_HASHES];
	int clearHashesPlace = 0;

	const int HASH_TABLE_SIZE = 160057;//64000031;//48000013;//;//
	Node hashTable[HASH_TABLE_SIZE];

	int insert(uint32_t num, uint32_t val, list<pair<int,int>>::iterator curIterator) {
		uint32_t hashIndex = num % HASH_TABLE_SIZE;

		//do linear probing
		if (hashTable[hashIndex].count == 0) {
			hashTable[hashIndex].lpiiIterator = curIterator;
			hashTable[hashIndex].value = num;
			//cerr << "New Element " << num  << " " << hashTable[hashIndex].count << endl;
			clearHashes[clearHashesPlace++] = hashIndex;
			return hashTable[hashIndex].count = 1;
		} else {
			if (hashTable[hashIndex].value == num) {
				hashTable[hashIndex].lpiiIterator = curIterator;
				hashTable[hashIndex].lpiiIterator->second = val;///little confused by this
				return ++hashTable[hashIndex].count;
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) {
						hashTable[hashIndex].lpiiIterator = curIterator;
						hashTable[hashIndex].lpiiIterator->second = val;
						return ++hashTable[hashIndex].count;
					}
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}

				hashTable[hashIndex].lpiiIterator = curIterator;
				hashTable[hashIndex].value = num;
				clearHashes[clearHashesPlace++] = hashIndex;
				return hashTable[hashIndex].count = 1;
			}
		}
	}

	pair<bool, list<pair<int,int>>::iterator> find(uint32_t num) {
		uint32_t hashIndex = num % HASH_TABLE_SIZE;

		//do linear probing
		if (hashTable[hashIndex].count == 0) return make_pair(false, hashTable[hashIndex].lpiiIterator);
		else {
			if (hashTable[hashIndex].value == num) {
				return make_pair(true,hashTable[hashIndex].lpiiIterator);
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) return make_pair(true, hashTable[hashIndex].lpiiIterator);
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}
				return make_pair(false,hashTable[hashIndex].lpiiIterator);
			}
		}
		
	}
	bool remove(int num) {
		uint32_t hashIndex = num % HASH_TABLE_SIZE;

		if (hashTable[hashIndex].count == 0) return false;
		else {
			if (hashTable[hashIndex].value == num) {
				hashTable[hashIndex].count = 0;
				return true;
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) {
						hashTable[hashIndex].count = 0;
						return true;
					}
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}
				return false;
			}
		}
	}
	void clear () {
		for(int i=0;i<clearHashesPlace;i++) {
			hashTable[clearHashes[i]].count = 0;
		}
		clearHashesPlace = 0;
	}
};

class LRUCache {
public:
	LRUCache(int capacity)
	{
		this->capacity = capacity;	
		this->myQueueSize = 0;
		HashTable::clear();
	}
	int get(int key) {
		//pair<bool, list<pair<int,int>>::iterator>
		auto inAndIterator = HashTable::find(key);
		if (inAndIterator.first) {
			myQueue.splice(myQueue.begin(), myQueue, inAndIterator.second);
			inAndIterator.second = myQueue.begin();
			return myQueue.begin()->second;
		}
		return -1;
	}
	void set(int key, int value) {
		if (myQueueSize == capacity) {
			auto inAndIterator = HashTable::find(key);
			if (!inAndIterator.first){ // if not in Q
				auto victim = move(myQueue.back());
				myQueue.pop_back(); //don't need to erase just move pointers
				HashTable::remove(victim.first);

				doFront(key,value);
			} else {
				myQueue.splice(myQueue.begin(), myQueue, inAndIterator.second);
				myQueue.begin()->second = value;
				inAndIterator.second = myQueue.begin();
			}
		} else {
			auto inAndIterator = HashTable::find(key);
			if (inAndIterator.first){// in Q
				myQueue.splice(myQueue.begin(), myQueue, inAndIterator.second);
				myQueue.begin()->second = value;
				inAndIterator.second = myQueue.begin();
			} else {
				++myQueueSize;
				doFront(key,value);
			}
		}
		//doFront(key,value);
	}
	void doFront(int key, int value) {
		myQueue.push_front(make_pair(key,value));
		HashTable::insert(key, value, myQueue.begin());
	}
	void printCache() {
		cout << "Printing cache" << endl;
		for(auto &x: myQueue) {
			cout << x.first << " " << x.second << ", ";
		}
	}
private:
	//unordered_map<int, pair<list<pair<int,int>>::iterator,bool>> myMap;
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
