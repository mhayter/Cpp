#include <bits/stdc++.h>
using namespace std;

bool visited[20010];

int main() {
	// your code goes here
	int n, m; cin >> n >> m;
	
	queue<pair<int,int>> que;
	que.push(make_pair(n,0));
	while (!que.empty()) {
		pair<int,int> temp = que.front(); que.pop();
		if (temp.first == m) {cout <<temp.second << endl; break;}
		if (temp.first <= 0 ) continue;
		if (temp.first >= 20005) continue;
		if (visited[temp.first]) continue;
		visited[temp.first] = true;
		int new1 = temp.first*2;
		int new2 = temp.first-1;
		if (new1 <= 2*m)
			que.push(make_pair(new1,temp.second+1));
		if (temp.first > 0)
			que.push(make_pair(new2,temp.second+1));
	}
	return 0;
}
