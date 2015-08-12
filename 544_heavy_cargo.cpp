#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int high=0;
unordered_map<string,int>myMap;
int getIndex(const string &s) {
	if (myMap.count(s))
		return myMap[s];
	else {
		return myMap[s]=high++;
	}
}

const int INF = 1000000000;
int graph[210][210];
int main() {
	int nCities, nRoads;
	int caseNum = 1;
	while (cin >> nCities >> nRoads) {
		if (nCities == 0 && nRoads == 0) break;

		for(int i=0;i<nCities;i++) {
			for(int j=0;j<nCities;j++) {
				graph[i][j] = 0;
			}
			//graph[i][i] = 0;
		}

		myMap.clear();
		high = 0;
		//cerr << "nRoads = "<< nRoads << endl;
		for (int i=0;i<nRoads;++i) {
			string to, from ; cin >> to >> from;
			int index1 = getIndex(to);
			int index2 = getIndex(from);

			int weight; cin >> weight;

			graph[index1][index2] = weight;
			graph[index2][index1] = weight;
			//cerr << graph[index1][index2] <<" "<< weight << endl;
			//edges[nEdges++] = Edge(index1,index2, weight);

		}

		
		for(int k=0;k<nCities;++k) {
			for(int i=0;i<nCities;++i) {
				for(int j=0;j<nCities;++j) {
					graph[i][j] = max(graph[i][j], min(graph[i][k],graph[k][j]));
				}
			}
		}
		
		string source, destination; cin >> source >> destination;
		int sourceIndex = getIndex(source); 
		int destinationIndex = getIndex(destination);
		//cerr << sourceIndex << " " << destinationIndex << endl;
		cout << "Scenario #" << caseNum++ << '\n';
		cout << graph[sourceIndex][destinationIndex] << " tons\n\n";

	}
	return 0;
}