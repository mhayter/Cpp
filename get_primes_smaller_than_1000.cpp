#include <iostream>
#include <vector>
using namespace std;

vector<int>primes;

bool isPrime(int n) {
	if (n<=2) return true;
	if (n%2==0) return false;
	for(int i=3;i*i<=n;i+=2) {
		if (n%i==0) return false;
	}
	return true;
}

int main() {
	for(int i=2;i<=1000;i++) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
	}
	cout << "int primes[" << primes.size() <<"] = {\n";
	for(int i=0;i+1<primes.size();i++) {
		if (i % 10 == 0) cout << endl;
		cout << primes[i] << ", ";
	}
	cout << primes[(int)primes.size()-1] << "};\n";
	return 0;
}