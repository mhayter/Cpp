#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <array>
using namespace std;

const int k = 10;

void doMod() {
	ifstream fin("ans.txt");
	string lines[k];
	string s;
	int nLines=0;
	while (getline(fin,s)) {
		lines[nLines++%k] = move(s);
	}
	for(int i=0;i<k;++i) {
		cout << "i = " << i << " " << lines[i] << '\n';
	}
}

void doReadTwice() {
	string curLine;
	int nLines = 0;
	{
		ifstream fin("ans.txt");
		while (getline(fin,curLine)) ++nLines;
	}
	{
		ifstream fin("ans.txt");

		int diff = nLines - k;
		for(int i=0;i<diff;++i) {
			//cout << "curLine = " << curLine << endl;
			getline(fin,curLine);
		}
		//cout << "hello" << endl;	
		while (getline(fin,curLine)) cout << curLine << '\n';
	}
}

void doDeque() {
	ifstream fin("ans.txt");
	deque<string>lines;
	int nLines = 0;
	string s;
	while (getline(fin,s)) {
		if (lines.size() < k) {
			lines.emplace_back(move(s));
		} else {
			lines.emplace_back(move(s));
			lines.pop_front();
		}
	}
	for(int i=0;i<lines.size();++i) {
		cout << lines[i] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	doMod();
	//doDeque();
	//doReadTwice();
	return 0;
}