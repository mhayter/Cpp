#include <bits/stdc++.h>
using namespace std;

vector<pair<pair<int,int>,string>> database;

vector<string> getMatches(int price) {
	vector<string>matches;
	for(int i=0;i<database.size();i++) {
		if (database[i].first.first <= price && price <=database[i].first.second){
			matches.push_back(database[i].second);
			if (matches.size() > 1) {
				return matches;
			}
		}
	}
	return matches;
}

int main() {
	int numCases; cin >> numCases;
	for(int caseNum=1;caseNum<=numCases;caseNum++) {
		database.clear();
		int databaseSize; cin >> databaseSize;
		for(int i=0;i<databaseSize;i++) {
			string name; cin >> name;
			int low, high; cin >> low >> high;
			database.push_back(make_pair(make_pair(low,high), name));
		}
		int nQueries; cin >> nQueries;
		for(int i=0;i<nQueries;i++) {
			int price; cin >> price;
			vector<string> matches = getMatches(price);
			if (matches.size() != 1) {
				cout << "UNDETERMINED\n";
			} else {
				cout << matches[0] << "\n";
			}
		}
		if (caseNum < numCases) cout << "\n";
	}
	return 0;
}