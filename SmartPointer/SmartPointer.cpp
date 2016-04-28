#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;

template<typename T>
class SmartPointer {
public:
	SmartPointer() : ptr(nullptr), count(0) {}
	SmartPointer(T *ptr) {this->ptr = ptr; count = 0; cerr << "Smart ctor" << endl;}
	SmartPointer(const SmartPointer &lhs): ptr(lhs.ptr), count(lhs.count) {
		cerr << "copy" << endl;
	}
	~SmartPointer() {
		delete ptr;
		ptr = nullptr;
		--count;
		cerr << "Smart dtor" << endl;
	}

	SmartPointer& operator=(SmartPointer lhs) {
		swap(ptr,lhs.ptr);
		swap(count,lhs.count);
		cerr << "assign" << endl;
		return *this;
	}

	T& operator*() {
		return *ptr;
	}

	T* operator->() {
	 	return ptr;
	 }

	T* operator&() {// not sure about
		return &ptr;
	}

private:
	T *ptr;
	int count;
};

struct State {
	State() : val(5) {
		cerr << "State ctor" << endl;
	}
	~State() {
		cerr << "State dtor" << endl;
	}
	int val;
};

int main() {
	SmartPointer<int> smartPtr(new int(5));
	cout << *smartPtr << endl;
	SmartPointer<State> statePtr(new State);
	(*statePtr).val;
	cout << "state ptr " <<statePtr->val << endl;
	return 0;
}