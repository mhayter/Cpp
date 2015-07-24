/*
ID: mhayter1
PROB: combo
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int n;
bool cond(int absx) {
	return (absx<=2 || absx==n-2 || absx==n-1);
}
bool getDist(int x,int y, int z, int nx,int ny, int nz) {
	int absx = abs(x-nx);
	int absy = abs(y-ny);
	int absz = abs(z-nz);
	//if(x==50 && y==50)
		//cout << "absz " << absz << endl;
	if ( cond(absx) && cond(absy) && cond(absz)) return true;
	return false;
}
int main() {
	// your code goes here
	ifstream fin("combo.in");
	ofstream fout("combo.out");
	
	fin >>n;
	int fx,fy,fz; fin >> fx >> fy >> fz;
	int cx,cy,cz; fin >> cx >> cy >> cz;
	int ans=0;
	for(int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			for (int k=1;k<=n;k++) {
				if (getDist(i,j,k,fx,fy,fz) || getDist(i,j,k,cx,cy,cz) ) {
					//cout << i <<","<<j<<","<<k<<endl;
					ans++;
				}
			}
		} 
	}
	fout << ans << endl;
	return 0;
}
