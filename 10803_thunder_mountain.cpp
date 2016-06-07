#include <bits/stdc++.h>
using namespace std;

const int MAX_CITIES = 110;
pair<int,int> cities[MAX_CITIES];
const int MAX_SQUARE_DIST = 10*10;
const double INF = 1e10;

int getDist(int y, int x, int ny, int nx) {
	return (ny-y)*(ny-y) + (nx-x)*(nx-x);
}

int main() {
	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		int nCities; cin >> nCities;
		for(int i=0;i<nCities;i++) {
			cin >> cities[i].first >> cities[i].second;
		}
		double weights[MAX_CITIES][MAX_CITIES];
		for(int i=0;i<nCities;i++) {
			for(int j=0;j<nCities;j++) {
				weights[i][j] = INF;
			}
		}
		for(int i=0;i<nCities;i++) {
			for(int j=i+1;j<nCities;j++) {
				int squareDist = getDist(	cities[i].first,cities[i].second, 
											cities[j].first,cities[j].second);
				if ( squareDist<= MAX_SQUARE_DIST) {

					weights[i][j] = weights[j][i] = sqrt(squareDist+0.);
				}
			}
		}
		for(int i=0;i<nCities;i++) {
			weights[i][i] = 0;
		}

		for(int k=0;k<nCities;k++) {
			for(int i=0;i<nCities;i++) {
				for(int j=0;j<nCities;j++) {
					double alt = weights[i][k]+weights[k][j];
					if (alt < weights[i][j]) {
						weights[i][j] = alt;
					}
				}
			}
		}
		double ans = -1;
		bool shortPathExists = true;
		for(int i=0;i<nCities;i++) {
			for(int j=i+1;j<nCities;j++) {
				if (weights[i][j]>1e9) {
					shortPathExists = false;
					break;
				}
				ans = max(weights[i][j],ans);
			}
		}
		printf("Case #%d:\n",caseNum);
		if (shortPathExists) {
			printf("%0.4f\n\n", ans);
		} else {
			printf("Send Kurdy\n\n");
		}

	}
	return 0;
}