#include <string>
#include <iostream>
using namespace std;

int main() {
	string line; cin >> line;
	int index = line.find('|');
	string p1 = line.substr(0,index);
	string p2 = line.substr(index+1);
	string other; cin >> other;

	for(int i=0;i<other.size();i++) {
		if (p1.size()<p2.size()) p1+=other[i];
		else p2+=other[i];
	}
	if (p1.size()!=p2.size()) cout << "Impossible" << endl;
	else cout << p1 << "|" << p2 << endl;
	return 0;
}