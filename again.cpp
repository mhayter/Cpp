#include <string>
#include <iostream>
using namespace std;

string numToString(int num) {
	string digits[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
	string others[] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};

	string tens[] = {"", "", "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

	string ans;

	if (num >=20) {
		//check for even on 
		if (num%10==0) ans = tens[num/10];
		else {
			ans = tens[num/10] + "-" + digits[num%10];
		}
	} else if (num >=10) {
		ans = others[num-10];
	} else {
		ans = digits[num];
	}
	return ans;
}

int main() {
	int num;
	cin >> num;
	cout << numToString(num) << endl;
	return 0;
}