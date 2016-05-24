#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

const int MAXSIZE= 1000010;
const int BASE = 7;
const long long MOD = 99999997;

long long hash1[MAXSIZE];
long long power1[MAXSIZE];

long long hash2[MAXSIZE];
long long power2[MAXSIZE];
int inputSize;



void hashIt(const string &s) {
    int n = inputSize = s.size();
    
    long long hash = 0;
    long long product = 1;
    for(int i=0; i < n; i++) {
        hash = (hash + product * (s[i] - 'a' + 1)) % MOD;
        power1[i] = product;
        product = (product * BASE) % MOD;
        hash1[i] = hash;
    }
    hash = 0;
    product = 1;
    for(int i=n-1; i>=0; i--) {
        hash = (hash + product * (s[i] - 'a' + 1)) % MOD;
        power2[i] = product; 
        product = (product * BASE) % MOD;
        hash2[i] = hash;
    }
}

void makePositive(long long &a) {
    if (a < 0) a = a + MOD;
}

bool hashCompare(int i, int j) {
    //find power
    long long forwardHashNumerator = (i==0) ? hash1[j] : (hash1[j] - hash1[i-1]);
    long long backwardHashNumerator = (j==inputSize-1) ? hash2[i] : (hash2[i] - hash2[j+1]);
    
    makePositive(forwardHashNumerator);
    makePositive(backwardHashNumerator);

    long long v1 = (forwardHashNumerator * power2[j]) % MOD;
    long long v2 =  (backwardHashNumerator * power1[i]) % MOD;
    
    return (v1 == v2);
}

int main() {
	ios_base::sync_with_stdio(false);
	string s; 
	while (true) {
		s = "";
		cin >> s;
		if (s.size() == 0) break;
		hashIt(s);

		int left = 0; 
		int right = (int)s.size() -1;
		string miss;
		while (left < right) {
			if (s[left] == s[right]) {
				int ostart = left;
				int oend = right;
				//test if pal

				if (hashCompare(left,right)) {
					break;
				} else {
					/*
					while (ostart<left) {
						miss += s[ostart++];
					}
					*/
					miss += s[ostart];
					left = ostart+1;
					right = oend;
				}

			} else {
				miss += s[left];
				left++;
			}
		}
		reverse(miss.begin(),miss.end());
		cout << s + miss << "\n";
	}
	return 0;
}