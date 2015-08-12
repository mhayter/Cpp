#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct State {
	State(){}
	State(int a, int b) :
		u(a), depth(b)
	{}

	int u;
	int depth;
};

const int SIZE = 26*26 + 10;
int parent[SIZE];
vector<int> adj[SIZE];
bool visited[SIZE];
string source, destination;

unordered_map<string,int>myMap;
unordered_map<int,string>reverseMap;
int curIndex;
int getIndex(string s) {
	if (myMap.count(s)) {
		return myMap[s];
	}
	reverseMap[curIndex] = s;
	return myMap[s] = curIndex++;
}

vector<string>path;
void printPath(int u) {
	if (u == -1) return;
	//cerr << "u = " << u << endl;
	printPath(parent[u]);
	path.push_back(reverseMap[u]);
	//cout << reverseMap[u] << ' ';
}

bool bfs() {
	int destinationIndex = getIndex(destination);
	queue<State> que;
	que.push(State(getIndex(source),0));
	bool solFound = false;

	while (!que.empty()) {
		State temp = que.front(); que.pop();
		if (visited[temp.u]) continue;
		//cerr << "temp.u " << temp.u << '\n';
		visited[temp.u] = true;
		if (temp.u == destinationIndex) {
			solFound = true;
			//cerr << "solFound" << endl;
			printPath(temp.u);
			//cout << '\n';
			break;
		}
		
		for(int i=0;i<adj[temp.u].size();++i) {
			int v = adj[temp.u][i];
			if (visited[v]) continue;
			parent[v] = temp.u;
			que.push(State(v,temp.depth+1));
		}
	}
	return solFound;
}

void init() {
	curIndex = 0;
	for(int i=0;i<SIZE;++i) {
		adj[i].clear();
		parent[i] = -1;
		visited[i] = false;
	}
	path.clear();
	myMap.clear();
	reverseMap.clear();
}
int main() {
	ios_base::sync_with_stdio(false);
	int nRoutes; 
	cin >> nRoutes;
	while (true) {
		init();
		for(int i=0;i<nRoutes;++i) {
			string u, v; cin >> u >> v;
			int uIndex = getIndex(u);
			int vIndex = getIndex(v);

			adj[uIndex].push_back(vIndex);
			adj[vIndex].push_back(uIndex);
		}
		cin >> source >> destination;
		
		if (!bfs()) cout << "No route\n";
		else {
			for(int i=0;i+1<path.size();i++) {
				cout << path[i] << " " << path[i+1] << endl;
			}
		}
		cin >> nRoutes;
		if (!cin.eof()) cout <<'\n';
		else break;
	}
	return 0;
}