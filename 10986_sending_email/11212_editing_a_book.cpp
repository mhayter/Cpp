#include <bits/stdc++.h>
using namespace std;

int N;

int hashIt(const vector<int> &a) {
	int hash = 0;
	for(auto &x:a) {
		hash = x+10*hash;
	}
	return hash;
}

int getDist(const vector<int> &a) {
	int tot=0;
	for(int i=0;i<a.size();i++) {
		int v = a[i];

		int destIndex = v - 1;
		if (destIndex!=i) tot++;
	}
	return tot;
}

int Astar(vector<int> &s,const vector<int> &dest) {
	set< pair<int, pair<int,vector<int> > > > que;
	unordered_map<int,bool> visited;

	que.insert(make_pair(getDist(s),make_pair(0,s)));
	while (!que.empty()) {
		int f = que.begin()->first;
		vector<int> temp = que.begin()->second.second;
		int g = que.begin()->second.first;
		que.erase(que.begin());

		if (temp == dest) {
			return g;
		}
		//if (visited.count(temp)) continue;
		//visited[temp] = true;

		cout << "g = " << g << endl;

		for(int start=0;start<N;start++) {
			for(int end=start;end+1<N;end++) {
				//rip out
				vector<int>vec1(temp.begin()+start,temp.begin()+end+1);
				temp.erase(temp.begin()+start,temp.begin()+end+1);

				for(int i=0;i<temp.size();i++) {
					vector<int>c = temp;
					c.insert(c.begin()+i,vec1.begin(),vec1.end());

					int v = hashIt(c);
					if (!visited.count(v)) {
						visited[v] = true;
						int newh=getDist(c);
						int newg=g+1;
						int newf = newh + newg;
						que.insert(make_pair(newf,make_pair(newg,c)));
					}
				}
				vector<int>c = temp;
				c.insert(c.begin()+temp.size(),vec1.begin(),vec1.end());

				int v = hashIt(c);
				if (!visited.count(v)) {
					visited[v]=true;
					int newh=getDist(c);
					int newg=g+1;
					int newf = newh + newg;
					que.insert(make_pair(newf,make_pair(newg,c)));
				}
				temp.insert(temp.begin()+start,vec1.begin(),vec1.end());
			}
		}

	}
	return 999;
}


int bfs(vector<int> &s,const vector<int> &dest) {
	queue< pair<vector<int>,int> > que;
	unordered_map<int,bool> visited;
	que.push(make_pair(s,0));
	while (!que.empty()) {
		vector<int> temp = que.front().first;
		int g = que.front().second;
		que.pop();

		if (temp == dest) {
			return g;
		}
		//if (visited.count(temp)) continue;
		//visited[temp] = true;

		//cout << "g = " << g << endl;

		for(int start=0;start<N;start++) {
			for(int end=start;end+1<N;end++) {
				//rip out
				vector<int>vec1(temp.begin()+start,temp.begin()+end+1);
				temp.erase(temp.begin()+start,temp.begin()+end+1);

				for(int i=0;i<temp.size();i++) {
					vector<int>c = temp;
					c.insert(c.begin()+i,vec1.begin(),vec1.end());

					int v = hashIt(c);
					if (!visited.count(v)) {
						visited[v] = true;
						que.push(make_pair(c,g+1));
					}
				}
				vector<int>c = temp;
				c.insert(c.begin()+temp.size(),vec1.begin(),vec1.end());

				int v = hashIt(c);
				if (!visited.count(v)) {
					visited[v]=true;
					que.push(make_pair(c,g+1));
				}
				temp.insert(temp.begin()+start,vec1.begin(),vec1.end());
			}
		}

	}
	return 999;
}

int main() {
	int caseNum=1;
	while (cin >> N && N) {
		vector<int>a(N,0);
		for(int i=0;i<N;i++) cin >> a[i];
		vector<int>dest(N,0);
		for(int i=0;i<N;i++) dest[i]=i+1;
		cout << "Case " << caseNum++ <<": "<< bfs(a,dest) << "\n";
	}
	return 0;
}