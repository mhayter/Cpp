#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int main() {
	int nCases; cin >> nCases;

	for(int caseNum=1;caseNum<=nCases;caseNum++) {

		
		int nBuildings; cin >> nBuildings;
		int nPaths; cin >> nPaths;

		int graph[nBuildings][nBuildings];

		for(int i=0;i<nBuildings;i++) {
			for(int j=0;j<nBuildings;j++) {
				graph[i][j]=INF;
			}
		}

		for(int i=0;i<nPaths;i++) {
			int u, v; cin >> u >> v;
			graph[u][v] = 1;
			graph[v][u] = 1; // maybe
		}
		int start, end; cin >> start >> end;

		for(int i=0;i<nBuildings;i++) graph[i][i] = 0;
		for(int k=0;k<nBuildings;k++) {
			for(int i=0;i<nBuildings;i++) {
				for(int j=0;j<nBuildings;j++) {
					if (graph[i][j] > graph[i][k]+graph[k][j]) {
						graph[i][j] = graph[i][k]+graph[k][j];
					}
				}
			}
		}

		/*for(int i=0;i<nBuildings;i++) {
			for(int j=0;j<nBuildings;j++) {
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}*/

		int ans = -INF;
		
		for(int i=0;i<nBuildings;i++) {
			int tot = 0;
			tot+=graph[start][i];
			tot+=graph[i][end];
			ans = max (ans,tot);
		}
		
		//get path from start to 
		cout << "Case "<<caseNum<<": " << ans << "\n";

	}
	return 0;
}