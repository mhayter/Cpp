#include <iostream>
#include <unordered_map>
#include <deque>
#include <list>

using namespace std;

//56ms assume perfect hash and don't delete memory
//60ms eliminated size in Doubly linked list
//60ms hand written Q
//64ms was memory limit exceeded

//76ms added splice to get, no diff
//76ms learned what splice was
//80ms reuse find iterator
//92ms list.size bad?

class Node {
public:
	Node(int key, int value, Node *prev, Node *next):
		key(key), value(value),
		prev(prev), next(next)
	{}
	int key;
	int value;
	Node *prev;
	Node *next;
};

class DoublyLinkedList{
public:
	DoublyLinkedList() {
		head = tail = nullptr;
		//size = 0;
	}
	~DoublyLinkedList() {}
	void pushFront(int key, int value) {
		if (!head) {
			head = tail = new Node(key, value,nullptr, nullptr);
		} else {
			Node *curNode = new Node(key,value, nullptr, head);
			head->prev = curNode;
			head = curNode;
		}
		//++size;
	}
	void popBack() {//have ohers delete
		//cout << "popBack" << endl;
		if (head){
			if (head == tail) head = nullptr;
			tail = tail->prev;
			if (tail) tail->next = nullptr;
			//--size;
		}
	}
	void print() {

		Node *curNode = head;
		int place = 0;
		while (curNode) {
			//cout << curNode->key << ":" << curNode->value << ",";
			curNode = curNode->next;
			++place;
		}
		cout << endl;
	}
	//int size;
	Node *head;
	Node *tail;
};

namespace HashTable {

	struct Node {
		int count;
		int value;
		::Node* lpiiIterator; 
	};
	const int MOST_UNIQUE_HASHES = 1010*10;
	unsigned clearHashes[MOST_UNIQUE_HASHES];
	int clearHashesPlace = 0;

	const int HASH_TABLE_SIZE = 160057;//64000031;//48000013;//;//
	Node hashTable[HASH_TABLE_SIZE];

	int insert(uint32_t num, uint32_t val, ::Node* curIterator) {
		uint32_t hashIndex = num ;//% HASH_TABLE_SIZE;

		//do linear probing
		if (hashTable[hashIndex].count == 0) {
			hashTable[hashIndex].lpiiIterator = curIterator;
			hashTable[hashIndex].value = num;
			//cerr << "New Element " << num  << " " << hashTable[hashIndex].count << endl;
			//clearHashes[clearHashesPlace++] = hashIndex;
			return hashTable[hashIndex].count = 1;
		} else {
			//Assume perfect hash
			/*

			if (hashTable[hashIndex].value == num) {
				hashTable[hashIndex].lpiiIterator = curIterator;
				hashTable[hashIndex].lpiiIterator->value = val;///little confused by this
				return ++hashTable[hashIndex].count;
			} else {
				//while a value exists and it's not the current one, advance
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) {
						hashTable[hashIndex].lpiiIterator = curIterator;
						hashTable[hashIndex].lpiiIterator->value = val;
						return ++hashTable[hashIndex].count;
					}
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}

				hashTable[hashIndex].lpiiIterator = curIterator;
				hashTable[hashIndex].value = num;
				clearHashes[clearHashesPlace++] = hashIndex;
				return hashTable[hashIndex].count = 1;
			}
			*/
			hashTable[hashIndex].lpiiIterator = curIterator;
			hashTable[hashIndex].value = num;
			//clearHashes[clearHashesPlace++] = hashIndex;
			return hashTable[hashIndex].count;
		}
	}

	pair<bool, ::Node *> find(uint32_t num) {
		uint32_t hashIndex = num;// % HASH_TABLE_SIZE;

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
		uint32_t hashIndex = num ;//% HASH_TABLE_SIZE;

		if (hashTable[hashIndex].count == 0) return false;
		else {
			if (hashTable[hashIndex].value == num) {
				hashTable[hashIndex].count = 0;
				return true;
			} else {
				//while a value exists and it's not the current one, advance
				/*
				hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				while (hashTable[hashIndex].count) {
					if (hashTable[hashIndex].value == num) {
						hashTable[hashIndex].count = 0;
						return true;
					}
					hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
				}
				*/
				return false;
			}
		}
	}
	void clear () {
		for(int i=0;i<MOST_UNIQUE_HASHES;i++) {
			hashTable[i].count = 0;
		}
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
#define moveToFront\
	if (inAndIterator.second != myQueue.head) {\
		if (inAndIterator.second->prev) inAndIterator.second->prev->next = inAndIterator.second->next;\
		if (inAndIterator.second->next) inAndIterator.second->next->prev = inAndIterator.second->prev;\
		if (inAndIterator.second == myQueue.tail) myQueue.tail = inAndIterator.second->prev;\
		inAndIterator.second->next = myQueue.head;\
		if (inAndIterator.second->next) inAndIterator.second->next->prev = inAndIterator.second;\
		inAndIterator.second->prev = nullptr;\
		myQueue.head = inAndIterator.second;\
	}
	int get(int key) {
		//pair<bool, list<pair<int,int>>::iterator>
		auto inAndIterator = HashTable::find(key);
		if (inAndIterator.first) {
			moveToFront;
			return myQueue.head->value;
		}
		return -1;
	}

#define doReassign\
		inAndIterator.second->value = value;\
		moveToFront;
		
	
#define doFront\
		myQueue.pushFront(key,value);\
		HashTable::insert(key, value, myQueue.head);

	void set(int key, int value) {
		auto inAndIterator = HashTable::find(key);
		if (myQueueSize == capacity) {
			if (!inAndIterator.first){ // if not in Q
				::Node* victim = myQueue.tail;
				myQueue.popBack();
				HashTable::remove(victim->key);
				//delete victim;
				doFront;
			} else {
				doReassign;
			}
		} else {
			if (inAndIterator.first){// in Q
				doReassign;
			} else {
				++myQueueSize;
				doFront;
			}
		}
		//doFront(key,value);
	}

	void printCache() {
		cout << "Printing cache" << endl;
		myQueue.print();
	}
//private:
	//unordered_map<int, pair<list<pair<int,int>>::iterator,bool>> myMap;
	DoublyLinkedList myQueue;
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
