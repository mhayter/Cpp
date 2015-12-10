#include <iostream>
#include <vector>
using namespace std;

struct State {
	int a;
	State() {cout << "Constructor" << endl;a = -1;}
	State(int v): a(v) {cout << "Con Value" << endl;}
	State(const State &rhs): a(rhs.a){
		cout << "Copy" << endl;
	}
	State &operator=(State rhs) {
		swap(a,rhs.a);
		cout << "Copy assign" << endl;
		return *this;
	}
	
	State (State &&rhs): a(move(rhs.a)){
		cout << "Move" << endl;
	}
	
	State& operator=(State &&rhs) {
		a = move(rhs.a);
		cout << "Move assign" << endl;
		return *this;
	}
	
};

State doIt() {
	cout << "in doit" << endl;
	State s;
	s.a = 5;
	return s;
}

int main() {
	// your code goes here
	State s;
	State start = doIt();
	cout << s.a << endl;
	cout << start.a << endl;
	vector<State>vals;
	//vals.reserve(10);
	vals.emplace_back(s);
	vals.emplace_back(s);
	cout << vals[0].a << " " << vals[1].a << endl;
	vals[1].a = 7;
	cout << vals[0].a << " " << vals[1].a <<" " <<s.a<< endl;
	vector<State>newVals;
	newVals.emplace_back(s);
	newVals.emplace_back(s);
	newVals.emplace_back(5);
	newVals.emplace_back(move(doIt()));
	newVals.emplace_back(move(doIt()));
	return 0;
}