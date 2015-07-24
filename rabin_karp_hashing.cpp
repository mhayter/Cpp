#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int MAXSIZE= 20010;
const int BASE = 7;
const long long MOD = 99999997;

long long hash1[MAXSIZE];
long long power1[MAXSIZE];

long long hash2[MAXSIZE];
long long power2[MAXSIZE];
int inputSize;



void hashIt(const string &s) {
    int n = s.size();
    
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

int getForwardHashSegment(int i, int j) {
    if (i==0) return hash1[j];
    return (hash1[j] - hash1[i-1])/pow(BASE,i);
}
int getBackwardHashSegment(int i, int j) {
    if (j == inputSize - 1) return hash2[i];
    return (hash2[i] - hash2[j+1])/pow(BASE,inputSize-j-1);
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

int containsPrefix(const string &a, int len) {
    for (int place = 0; place + len <= inputSize; place++) {
        //test it with hash [len + place - 1 ... place]
        /*int forwardHashSegment = getForwardHashSegment(place, place+len-1);
        int backwardHashSegment = getBackwardHashSegment(place, place+len-1);
        if (forwardHashSegment == backwardHashSegment) return place;
        */
        if (hashCompare(place,place+len-1)) return place;
    }
    return -1;
}

int binarySearch(const string &input, int high) {
    int low = 0;
    int mid;
    while (low <= high) {
        mid = low + (high-low) / 2;
        cout << "mid = " << mid << endl;
        if (containsPrefix(input, mid) != -1) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low-1;
}

int main()
{
   cout << "mod " << MOD << endl;
   string input;
   cin >> input;
   inputSize = input.size();
   hashIt(input);
   int ans = 0;
   cout << binarySearch(input, inputSize) << endl;
   /*
   for (int len = inputSize; len >=0; len--) {
       //test for prefix of this length
       int index = containsPrefix(input,len);
       if (index != -1) {
           cout <<" at " << index << endl;
           ans = len;break;
       }
   }
   cout << ans << endl;
   */
   return 0;
}
   
