#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int main() {
	int nPeople, budget, nHotels, nWeeks;
	while (cin >> nPeople >> budget >> nHotels >> nWeeks) {
		int minTot = budget;
		for (int i=0;i<nHotels;i++) {
			int rate; cin >> rate;
			//cout << "rate " << rate << endl;
			for(int j=0;j<nWeeks;j++) {
				int nBeds; cin >> nBeds;
				//cout << "nBeds " << nBeds << endl;
				if (nBeds >= nPeople) {
					//cout << "yep" << endl;
					minTot = min(minTot, rate * nPeople);
				}
			}
		}
		//cout << "ans ";
		if (minTot == budget) {
			cout << "stay home" << endl;
		} else {
			cout << minTot << endl;
		}
	}
	return 0;
}