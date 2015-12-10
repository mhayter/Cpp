#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

class Game {
public:
	Game(int nTimes=10000, int oTotal=17000, int totalBet=20000, int betSize=500) {
		static int a[6] = {40, 30, 6, 3, 1, -1};
		static int p[6] = {2172, 2353, 32579, 49593, 169412, 743891};//1000000
		int accumulatedP[6];
		accumulatedP[0] = p[0];
		for(int i=1;i<6;i++) {
			accumulatedP[i] = accumulatedP[i-1] + p[i];
		}
		int wentBroke = 0;
		int nGood = 0;
		int nTenGrand = 0;
		for(int i=0;i<nTimes;i++) {
			//bet
			int total = oTotal;
			for(int bets = 0; bets < totalBet/betSize; bets++) {
				int num = rand()%1000000;

				for(int j=0;j<6;j++) {
					if (num <= accumulatedP[j]) {
						total += a[j] * betSize;
						break;
					}
				}
				//cerr << "total " << total << endl;
				if (total <=0) {
					wentBroke++;
					break;
				} 
			}
			if (total -oTotal >=5000) {
				nGood++;
			}
			if (total - oTotal >= 10000) {
				nTenGrand++;
			}
		}
		cout << nTimes << " played. Ruined: " << (0.+wentBroke)/ nTimes *100 << " percent" << endl;
		cout << "Made 5000 " << (0.+nGood)/nTimes *100 << " percent" << endl;
		cout << "Made 10000 " << (0.+nTenGrand)/nTimes *100 << " percent" << endl;
	}
};



int main() {
	Game g;
	return 0;
}