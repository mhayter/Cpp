#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1000*1000*10;

int my_stoi(const string &a) {
	stringstream ss(a);
	int ans;
	ss >> ans;
	return ans;
}

int a[SIZE];

int main(int argc, char *argv[]) {
	//int a2[SIZE];
	int n;
	string s="123456789";

	for(int i=0;i<SIZE;i++) {
		if (argv[1]=="--stoi")
			a[i] = stoi(s);
		else 
			a[i] = my_stoi(s);
	}
	return 0;
}