#include <string>
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;

const int MOD = 67867967;

int main() {
	string line;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	unordered_map<long long,char *>myMap;
	while (true) {
		char a[23] = {'\0'};
		fgets(a,23,stdin);
		if (a[0] == '\n' || a[0]==(char)13) break;
		char *s1 = new char[11];
		char s2[11]={'\0'};
		//sscanf(a,"%s %s\n",s1,s2);
		int index = 0;
		char *aPtr = a;
		char *s1Ptr = s1;

		while (*aPtr != ' ') {
			*s1Ptr++ = *aPtr++;
		}
		//cerr << "s1 " << s1 << endl;
		//cerr << "space#"<<*aPtr++ <<"#"<< endl;
		long long hash = 0;
		char *s2Ptr = s2;
		while (*aPtr>='a' && *aPtr <='z') {
			*s2Ptr++ = *aPtr;
			hash = hash*26 + (*aPtr++ - 'a');
		}
		s2Ptr = s2;
		/*for(int i=0;s2[i];i++) {
			cerr << (char)s2[i] << " ";
		}
		cerr << endl;*/
		myMap[hash] = s1;
	}
	
	while (true) {
		char a[12] = {'\0'};
		if(!fgets(a,12,stdin)) break;
		//hash it
		char *b = a;
		long long hash = 0;
		while (*b != '\n' && *b != (char)13) {
			hash = hash*26+(*b++ - 'a');
			//if (hash >= MOD) hash %= MOD;
		}
		if (myMap.count(hash)) {
			puts(myMap[hash]);
		} else {
			puts("eh");
		}
	}
	
	return 0;
}