#include "my_fast_io.h"
using namespace std;

int main() {
	FastInput input;
	FastOutput output;

	int n = input.ReadNext();
	output.PrintUint(n,'\n');
	output.Flush();
	return 0;
}