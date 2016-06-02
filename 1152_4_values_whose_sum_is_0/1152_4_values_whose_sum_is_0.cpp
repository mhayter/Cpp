#include <bits/stdc++.h>
using namespace std;

//3.950s remove if statement 
//3.380s reserve map
//5.02s -> 4.820s  int works despite wrong

const int SIZE = 4010;
int A[SIZE];
int B[SIZE];
int C[SIZE];
int D[SIZE];

unordered_map<int,int> ABSum;
//vector<int> clearHashes;

void reset() {
	ABSum.clear();
}

int main() {
	ABSum.reserve(SIZE*SIZE);
	//clearHashes.reserve(SIZE*SIZE);

	ios_base::sync_with_stdio(false);
	int nCases; cin >> nCases;

	for(int caseNum=1; caseNum<=nCases;caseNum++) {
		int arrayLength; cin >> arrayLength;
		for(int i=0;i<arrayLength;i++) {
			cin >> A[i] >> B[i] >> C[i] >> D[i];
		}

		//Do A+B sums
		
		//ABSum.reserve(arrayLength*arrayLength);
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				int sum = A[i] + B[j];
				ABSum[sum]++;
				//clearHashes.emplace_back(sum);
			}
		}

		int tot = 0;
		for(int i=0;i<arrayLength;i++) {
			for(int j=0;j<arrayLength;j++) {
				int sum = C[i] + D[j];
				auto it = ABSum.find(-sum);
				if (it != ABSum.end())
					tot += it->second;
			}
		}
		cout << tot << "\n";
		if (caseNum != nCases) {
			reset(); 
			cout << "\n";
		}
	}
	return 0;
}