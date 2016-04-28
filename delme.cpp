#include <iostream>
#include <deque>
using namespace std;

struct State {
	State(){y=x=-1;cout << "def ctor\n";}
	State (int a,int b) {y=a;x=b; cout << "Reg ctor\n";}
	State(const State &s) {cout << "cctor\n";}
	State(State &&s) {cout << "move cctor\n";}
	
	
	int y;
	int x;
};

int main() {
	
	deque<State>myQue;
	myQue.push_front(State(4,4));
	State myState(1,2);
	myQue.push_front(myState);
	myQue.push_front(State(1,2));
	for (int i=0;i<myQue.size();i++) {
		cout << myQue[0].y << " " << myQue[0].x<< endl;
	}
	cout << myQue[0].y << " " << myQue[1].y << endl;
	
	State s = myQue.front(); myQue.pop_front();
	State news = myQue.front();
	cout <<"s " <<  s.y << endl;
	cout <<"news " << news.y << endl;
	
	// your code goes here
	return 0;
}