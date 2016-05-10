#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	int nKeywords, nExcuses;
	int caseNum = 1;
	vector<pair<int,string>>bestExcuses;
	cin >> nKeywords >> nExcuses;
	getline(cin,s);
	while (true) {
		bestExcuses.clear();
		unordered_set<string>mySet;
		for(int i=0;i<nKeywords;i++) {
			getline(cin, s);

			mySet.insert(s);
		}
		for(int i=0;i<nExcuses;i++) {
			getline(cin,s);
			string ostr = s;
			for(int j=0;j<s.size();j++) {
				if (!isalpha(s[j])) {
					s[j] = ' ';
				} else {
					s[j] = tolower(s[j]);
				}
			}
			stringstream ss(s);
			string word;
			int cnt = 0;
			while (ss >> word) {
				if (mySet.count(word)>0) {
					cnt++;
				}
			}
			if (bestExcuses.size() == 0) {
				bestExcuses.push_back(make_pair(cnt,ostr));
				continue;
			}
			if (cnt == bestExcuses[0].first) {
				bestExcuses.push_back(make_pair(cnt,ostr));
			} else if (cnt > bestExcuses[0].first) {
				bestExcuses.clear();
				bestExcuses.push_back(make_pair(cnt, ostr));
			} else {
				//don't worry good excuse
			}
			
		}
		cout << "Excuse Set #" << caseNum++ << "\n";
		for(int i=0;i<bestExcuses.size();i++) {
			cout << bestExcuses[i].second << "\n";
		}
		cout << "\n";
		if (!(cin >> nKeywords >> nExcuses)) {
			break;
		} else {
			getline(cin,s);
		}
	}
	return 0;
}