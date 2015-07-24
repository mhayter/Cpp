#include <iostream>
using namespace std;

const int TICKS = 40;

const int DEG_PER_TICK = 360/TICKS;

int getClockwise(int &start,int &end) { // decrease #
	if (start>=end) {// good
		//start = end;
		return (start - end)*DEG_PER_TICK;
	} else {
		//start = end;
		return (TICKS+start-end)*DEG_PER_TICK;
	}
}

int getCounterClockwise(int &start,int &end) {
	if (start<=end) {
		//start = end;
		return (end - start)*DEG_PER_TICK;
	} else {
		//start = end;
		return (TICKS+end-start)*DEG_PER_TICK;
	}
}

int main() {
	int start, c1, c2, c3;
	while (true) {
		cin >> start >> c1 >> c2 >> c3;
		if (start==0 && c1==0 && c2==0 && c3==0) break;
		int ans = 0;

		ans += 360*2; // 2 clockwise

		//clockwise
		ans +=getClockwise(start,c1);
		start = c1;
		//cout << ans << endl;
		//counter clockwise
		ans+=360;
		ans += getCounterClockwise(start,c2);
		start=c2;
		//cout << ans << endl;
		//clockwise (no full turn?)
		ans += getClockwise(start,c3);
		start = c3;

		//cout << "true ";
		cout << ans << endl;
	}
	return 0;
}