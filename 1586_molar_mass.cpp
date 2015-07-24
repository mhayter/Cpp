#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;

char list[]="CHON";
double weight[]={12.01, 1.008,16,14.01};

double getWeight(char c, int amount) {
	double tot=0;
	for(int i=0;i<4;i++) {
		if (list[i]==c) return weight[i]*amount;
	}
	return tot;
}


char getChar(int &p, string &s) {
	if (isalpha(s[p])){
		return s[p++];
	}
	return '#';
}

int getAmount(int &p, string &s) {
	int amount = 0;
	bool in = false;
	for(;p<s.size() && isdigit(s[p]);p++) {
		amount = amount * 10 + s[p]-'0';
		in = true;
	}
	if (in) return amount;
	return 1;
}


int main() {
	int n; cin >>n;
	for(int i=0;i<n;i++) {
		string line; cin >> line;
		char c; int amount = 1;
		int p = 0;
		double tot = 0;
		while (true) {
			c = getChar(p,line);
			amount = getAmount(p,line);
			//cout << c << " " << amount << endl;
			tot+=getWeight(c,amount);
			//cout << tot << endl;
			amount = 1;
			if (p >= line.size()) break;
		}
		printf("%.3f\n", tot);
		//cout << tot << "\n";
	}
	return 0;
}