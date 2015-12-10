#include <iostream>
#include <set>
#include <vector>

#include <cstring>
#include <cstdio>
using namespace std;

//tied #1 0.000s (not unique)
//Plug and chug dijkstra one based
class FastInput {
public:
FastInput() {
m_dataOffset = 0;
m_dataSize = 0;
m_v = 0x80000000;
}
uint32_t ReadNext() {
if (m_dataOffset == m_dataSize) {
int r = fread(m_buffer,1,sizeof(m_buffer),stdin);
if (r <= 0) return m_v;
m_dataOffset = 0;
m_dataSize = 0;
int i = 0;
if (m_buffer[0] < '0') {
if (m_v != 0x80000000) {
m_data[m_dataSize++] = m_v;
m_v = 0x80000000;
}
for (; (i < r) && (m_buffer[i] < '0'); ++i);
}
for (; i < r;) {
if (m_buffer[i] >= '0') {
m_v = m_v * 10 + m_buffer[i] - 48;
++i;
} else {
m_data[m_dataSize++] = m_v;
m_v = 0x80000000;
for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
}
}
}
return m_data[m_dataOffset++];
}
public:
uint8_t m_buffer[32768];
uint32_t m_data[16384];
size_t m_dataOffset, m_dataSize;
uint32_t m_v;
};

const int INF = 1000000000;
const int SIZE = 110;

vector<pair<int,int>>graph[SIZE];
int dist[SIZE];

void dijkstra(int source, int n, int m) {
	for(int i=0;i<n;i++) dist[i] = INF;
	
	set<pair<int,int>>que;
	dist[source]=0;
	que.insert(make_pair(0,source));
	
	while (!que.empty()) {
		int u = que.begin()->second;
		int w = que.begin()->first;
		que.erase(que.begin());
		
		for(auto &p:graph[u]) {
			int alt = dist[u] + p.first;
			int v = p.second;
			if (alt < dist[v]) {
				dist[v] = alt;
				que.insert(make_pair(dist[v],v));
			}
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	FastInput input;
	int nCases=input.ReadNext();


	for(int numCase=1;numCase<=nCases;numCase++) {

		int n=input.ReadNext()+1;
		int destination=input.ReadNext();
		int maxTime = input.ReadNext();
		int m=input.ReadNext();

		for(int i=0;i<n;i++) graph[i].clear();
		for(int i=0;i<m;i++) {
			int u = input.ReadNext();
			int v = input.ReadNext();
			int w = input.ReadNext();
			graph[v].push_back(make_pair(w,u)); //reverse the edges
		}
		dijkstra(destination,n,m);
		int ans = 0;
		for(int i=1;i<n;i++) {
			if (dist[i] <= maxTime) {
				++ans;
			}
		}
		cout << ans << '\n';
		if (numCase < nCases) cout << '\n';
	}
	return 0;
}
