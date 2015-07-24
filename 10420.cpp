#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

//wrong

int main() {
	string line;
	int n; 

	while(cin >> n) {
		getline(cin,line);
		map<string,vector<string>> myMap;
		for(int i=0;i<n;i++) {
			getline(cin,line);
			stringstream ss(line);

			string country;
			ss >> country;
			//cout << " country " << country;

			string name = ss.str();
			if (myMap.count(country)) {
				bool found = false;
				for(int i=0;i<myMap[country].size();i++) {
					if (myMap[country][i] == name) {
						found = true;
						break;
					}
				}
				//if (!found) {
					myMap[country].push_back(name);
				//}
			} else{
				myMap[country].push_back(name);
			}

		}
		for(auto &x:myMap) {
			cout << x.first << " " << x.second.size() << "\n";
		}
	}
	return 0;
}