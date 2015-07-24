#include <iostream>
#include <set>
#include <vector>

#include <cstring>
#include <cstdio>
using namespace std;

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
class FastOutput {
public:
FastOutput() {
m_dataOffset = 0;
}
~FastOutput() {
}
void Flush() {
if (m_dataOffset) {
if (fwrite(m_data,1, m_dataOffset,stdout));
m_dataOffset = 0;
}
}
void PrintUint(uint32_t v, char d) {
if (m_dataOffset + 11 > sizeof(m_data)) Flush();
if (v < 100000) {
if (v < 1000) {
if (v < 10) {
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 1;
} else if (v < 100) {
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 2;
} else {
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 3;
}
} else {
if (v < 10000) {
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 4;
} else {
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 5;
}
}
} else {
if (v < 100000000) {
if (v < 1000000) {
m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 6;
} else if (v < 10000000) {
m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 7;
} else {
m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 8;
}
} else {
if (v < 1000000000) {
m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 9;
} else {
m_data[m_dataOffset + 9] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48; v /= 10;
m_data[m_dataOffset + 0] = v + 48;
m_dataOffset += 10;
}
}
}
m_data[m_dataOffset++] = d;
}
void PrintChar(char d) {
if (m_dataOffset + 1 > sizeof(m_data)) Flush();
m_data[m_dataOffset++] = d;
}
void ReplaceChar(int offset, char d) {
m_data[m_dataOffset + offset] = d;
}

void PrintStr(const char *str) {
	if (strlen(str) + m_dataOffset > sizeof(m_data)) Flush();
	while (m_data[m_dataOffset++] = *str++);
}
public:
uint8_t m_data[32768];
size_t m_dataOffset;
};

const int INF = 1000000000;
const int SIZE = 20010;

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

		int n=input.ReadNext();
		int m=input.ReadNext();
		int source=input.ReadNext();
		int destination=input.ReadNext();

		for(int i=0;i<n;i++) graph[i].clear();
		for(int i=0;i<m;i++) {
			int u = input.ReadNext();
			int v = input.ReadNext();
			int w = input.ReadNext();
			graph[u].push_back(make_pair(w,v));
			graph[v].push_back(make_pair(w,u));
		}
		dijkstra(source,n,m);
		cout << "Case #" << numCase <<": ";
		if(dist[destination]==INF) 
			cout << "unreachable" << "\n";
		else 
			cout << dist[destination] << "\n";
	}
	return 0;
}
