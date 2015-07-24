#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int numPeople, numConnections;
    int counter = 1;
    while (true) {
        cin >> numPeople >> numConnections;
        if (numPeople == 0) break;
        for(int i=0; i < numConnections;i++) {
                string to, from;
                cin >> to >> from;
                int toIndex = getIndex(to);
                int fromIndex = getIndex(from);
                
                graph[toIndex][fromIndex] = graph[fromIndex][toIndex] = 1;
        }
        for(int i=0; i < numPeople;i++)for(int j=0;j<numPeople;j++) graph[i][j]=1000;
        for(int i=0; i < numPeople; i++) graph[i][i] = 0;
        
        // do floyd
        for(int k=0; k < numPeople; k++) {
                for(int i=0; i < numPeople; i++) {
                        for(int j=0; j < numPeople; j++) {
                                if(graph[i][j] > graph[i][k] + graph[k][j]){
                                               graph[i][j] = graph[i][k] + graph[k][j];
                                }
                        }
                }
        }
        
        //check for max dist
        int maxDist = -1000;
        for(int i=0; i < numPeople; i++) {
                for(int j=i; j<numPeople;j++) {
                        maxDist = max(maxDist, graph[i][j]);
                }
        }
        
        cout << "Network " << counter++ << ": " << (maxDist<1000)? maxDist : "DISCONNECTED" << "\n\n";
                
            
