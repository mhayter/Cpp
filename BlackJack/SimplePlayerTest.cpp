#include <iostream>
#include <type_traits>
#include <cassert>

#include "SimplePlayer.h"
using namespace std;

int main() {

	SimplePlayer sp;

	sp.lose();
 	cerr << sp.money << endl;
	assert(sp.money == 975);
	sp.win();

	assert(sp.money == 1000);


	return 0;
}