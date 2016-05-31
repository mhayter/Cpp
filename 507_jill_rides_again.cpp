#include <bits/stdc++.h>
using namespace std;


//From 0.180s -> 0.050s sync_with_stdio(false);

const int SIZE = 20010;
int a[SIZE];

int main() {
	ios_base::sync_with_stdio(false);
	int nRoutes; cin >> nRoutes;
	for(int i=0;i<nRoutes;i++) {
		int nStops; cin >> nStops;
		for(int j=0;j+1<nStops;j++) {
			cin >> a[j];
		}
		int place = 0;
		int sum = 0; // ll ?
		int start = 0;
		int stop = 0;
		int maxStart = 0;
		int maxStop = 0;
		int maxDist = 0;
		int maxSum = 0;
		while (place +1 < nStops) {
			if(sum + a[place] >= 0){
				sum += a[place];
				//cerr << "place " << place << " a " << a[place] << " sum " << sum << endl;
				if (sum > maxSum) {
					maxSum = sum;
					stop = place;
					maxStart = start;
					maxStop = stop;
					maxDist = maxStop - maxStart;
				} else if (sum == maxSum) {
					stop = place;
					if (stop - start> maxDist) {
						maxDist = stop-start;
						maxStart = start;
						maxStop = stop;
					}
				}
			} else {
				start = stop = place+1;
				sum = 0;
			}
			place++;
		}
		if (maxSum > 0)
			cout << "The nicest part of route " << i+1 << " is between stops " << maxStart+1 << " and " << maxStop+2 << "\n";
		else {
			cout << "Route " << i+1 << " has no nice parts\n";
		}

	}
	return 0;
}