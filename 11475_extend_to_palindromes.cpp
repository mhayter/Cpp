#include <iostream>
#include <string>
#include <algorithm>


using namespace std;


int main() {
	string s; 
	while (true) {
		s = "";
		cin >> s;
		if (s.size() == 0) break;
		int left = 0; 
		int right = (int)s.size() -1;
		string miss;
		while (left < right) {
			if (s[left] == s[right]) {
				int ostart = left;
				int oend = right;
				while (left < right && s[left] == s[right]) {
					left++;
					right--;
				}
				if (left >= right) { // pal found
					break;
				} else {
					/*
					while (ostart<left) {
						miss += s[ostart++];
					}
					*/
					miss += s[ostart];
					left = ostart+1;
					right = oend;
				}

			} else {
				miss += s[left];
				left++;
			}
		}
		reverse(miss.begin(),miss.end());
		cout << s + miss << "\n";
	}
	return 0;
}