#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
	int nSwap;
	while (cin >> nSwap && nSwap!=0) {
		string s; cin >> s;
		//cerr << "s = " << s << endl;
		nSwap = (int)s.size()/nSwap;
		for(int i=0;i<s.size();i+=nSwap) {
			for(int j=i,nTimes=1;nTimes<=nSwap/2 && j<s.size();j++,nTimes++) {
				//cerr << "in " << j << " " <<j+nSwap-nTimes<<endl;
				swap(s[j],s[i+nSwap-nTimes]);
			}
			//cerr << "s after " << i << " " << s << endl;
		}
		cout << s << endl;
	}
	return 0;
}