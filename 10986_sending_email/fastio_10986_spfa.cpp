//#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;

//got 0.055s
//2x as fast using vector


//Certified #1 7/15/2015
#define SLF

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
const int SIZE=20010;
const int INF=1000000000;
int dist[SIZE];

//w,v
vector<pair<int,int>> adj[SIZE];

struct Edge {
	int w;
	int v;
};

//Edge edges[SIZE][SIZE/2];

int deg[SIZE];

int que[SIZE*100];
int qf,qe;
//bool inq[SIZE];

bitset<SIZE>inq;

int SPFA(int n, int source, int destination) {
	inq = 0;
	for(int i=0;i<=n;i++) {
		dist[i]=INF;
	}
	qf=qe=0;
	
	dist[source]=0;

	//queue<int>que;
	//que.push(source);

	que[qe++] = source; // push source
	inq[source]=true;

	int u,v,w;
	while (qf != qe) {
		//int u = que.front();que.pop();
		int u = que[qf++];
		//if (qf == SIZE) qf = 0;

		inq[u] = false;
		
		for(auto &x:adj[u]) {
			v = x.second;
			w = x.first;

			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if (!inq[v]){
					//que.push(v);
					que[qe++] = v;
					#ifdef SLF
					//small label first SLF
					if (dist[que[qe-1]] < dist[que[qf]]) {
						int toPush = que[--qe];
						que[qf++] = toPush;
					}
					#endif
					//if (qe == SIZE) qe = 0;
					inq[v]=true;
				}
			}
		}
	}
	return dist[destination];
}

int SPFA_SLF(int n, int source, int destination) {
	inq = 0;
	for(int i=0;i<=n;i++) {
		dist[i]=INF;
	}
	qf=qe=0;
	
	dist[source]=0;

	//queue<int>que;
	//que.push(source);
	deque<int>que;

	que.push_back(source);
	//que[qe++] = source; // push source
	inq[source]=true;

	int u,v,w;
	while (!que.empty()) {
		//int u = que.front();que.pop();
		int u = que.front(); que.pop_front();
		//if (qf == SIZE) qf = 0;

		inq[u] = false;
		
		for(auto &x:adj[u]) {
			v = x.second;
			w = x.first;

			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if (!inq[v]){
					//que.push(v);
					que.push_back(v);

					#ifdef SLF
					//small label first SLF
					if (dist[que.back()] < dist[que.front()]) {
						int toPush = que.back(); que.pop_back();
						que.push_front(toPush);
					}
					#endif
					//if (qe == SIZE) qe = 0;
					inq[v]=true;
				}
			}
		}
	}
	return dist[destination];
}

int main() {
	FastInput input;
	//FastOutput output;
	int nCases = input.ReadNext();
	int n,m,source,destination;
	int u,v,w;
	int i;
	for(int numCase=1;numCase<=nCases;numCase++) {

		n=input.ReadNext();
		m=input.ReadNext();
		source=input.ReadNext();
		destination=input.ReadNext();

		for(i=0;i<=n;i++) adj[i].clear();
		//for(i=0;i<=n;i++) deg[i] = 0;

		for(i=0;i<m;i++) {
			u = input.ReadNext();
			v = input.ReadNext();
			w = input.ReadNext();

			//edges[u][deg[u]++] = {w,v};

			//edges[v][deg[v]++] = {w,u};

			adj[u].push_back(make_pair(w,v));
			adj[v].push_back(make_pair(w,u));
		}
		SPFA_SLF(n,source,destination);
		/*
		output.PrintStr("Case #");
		output.PrintUint(numCase,':');
		output.PrintChar(' ');
		*/
		//cout << "Case #" << numCase <<": ";
		if(dist[destination]==INF) {
			//output.PrintStr("unreachable\n");
			printf("Case #%d: unreachable\n",numCase);
			//cout << "unreachable" << "\n";
		} else { 
			//output.PrintUint(dist[destination],'\n');
			printf("Case #%d: %d\n", numCase, dist[destination]);
			//cout << dist[destination] << "\n";
		}
	}
	//output.Flush();
	return 0;
}