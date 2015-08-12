#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <set>
using namespace std;

//certified #1
//only works on bidirectional for now reverse follow edges latter
//http://www.cs.princeton.edu/courses/archive/spr06/cos423/Handouts/EPP%20shortest%20path%20algorithms.pdf

#define SLF
#define LLL

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
	int toPush;
	int avg;
	#ifdef LLL
	int tot = 0;
	#endif
	while (!que.empty()) {
		//int u = que.front();que.pop();
		int u = que.front(); que.pop_front();
		//if (qf == SIZE) qf = 0;

		inq[u] = false;
		#ifdef LLL
		tot -= dist[u];
		#endif
		
		for(auto &x:adj[u]) {
			v = x.second;
			w = x.first;

			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				if (!inq[v]){
					//que.push(v);
					que.push_back(v);

					#ifdef LLL
					tot += dist[v];
					#endif

					#ifdef SLF
					//small label first SLF
					if (dist[v] < dist[que.front()]) {
						toPush = v; que.pop_back();
						que.push_front(toPush);
					}
					#endif
					#ifdef LLL
					avg = tot/que.size();
					while (dist[que.front()] > avg) {
						toPush = que.front(); que.pop_front();
						que.push_back(toPush);
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

int dijkstra(int source, int n,int dest) {
	for(int i=0;i<n;i++) dist[i] = INF;
	
	set<pair<int,int>>que;
	dist[source]=0;
	que.insert(make_pair(0,source));
	
	while (!que.empty()) {
		int u = que.begin()->second;
		if (u == dest) return dist[dest];
		int w = que.begin()->first;
		que.erase(que.begin());
		
		for(auto &p:adj[u]) {
			int alt = dist[u] + p.first;
			int v = p.second;
			if (alt < dist[v]) {
				dist[v] = alt;
				que.insert(make_pair(dist[v],v));
			}
		}
	}
	#ifdef DEBUG
	for(int i=0;i<=nRows*nCols;i++) {
		cerr <<"i " << i << " " << dist[i] << endl;
	}
	#endif
	return dist[dest];
}

int Fdist[SIZE];
int Bdist[SIZE];
bitset<SIZE> Fprocessed,Bprocessed;
int dijkstraBidirectional(int source, int n,int dest) {
	if (source == dest) return 0;
	for(int i=0;i<n;i++) {Fdist[i] = Bdist[i] = INF;}
	
	set<pair<int,int>>Fque,Bque;
	Fprocessed = Bprocessed = 0;
	Fdist[source]=0; Bdist[dest]=0;
	
	Fque.insert(make_pair(0,source));
	Bque.insert(make_pair(0,dest));

	int minDist = INF;

	int Fu,Bu;
	int alt, v;

	while (Fque.size() || Bque.size()) {
		if (Fque.size()) {
			if (Bque.begin()->first + Fque.begin()->first >= minDist) return minDist;
			Fu = Fque.begin()->second;
			Fque.erase(Fque.begin());
			
			for(auto &p:adj[Fu]) {
				alt = Fdist[Fu] + p.first;
				v = p.second;
				if (alt < Fdist[v]) {
					Fdist[v] = alt;
					if (Bprocessed[v]) {
						minDist = min(minDist,Fdist[Fu]+Bdist[v]+p.first);
					}
					Fque.insert(make_pair(alt,v));
				}
			}
			Fprocessed[Fu] = 1;
		}
		if (Bque.size()) { 
			//cerr << "B in" << endl;
			if (Bque.begin()->first + Fque.begin()->first >= minDist) return minDist;
			Bu = Bque.begin()->second;	
			Bque.erase(Bque.begin());
				
			for(auto &p:adj[Bu]) {
				alt = Bdist[Bu] + p.first;
				v = p.second;
				if (alt < Bdist[v]) {
					Bdist[v] = alt;
					if (Fprocessed[v]) {
						minDist = min (minDist, Bdist[Bu]+Fdist[v]+p.first);
					}
					Bque.insert(make_pair(alt,v));
				}
			}
			Bprocessed[Bu] = 1;
		}

	}
	return INF;
}

int dijkstraCrazyQueue(int source, int n,int dest,int maxWeight) {
	for(int i=0;i<n;i++) dist[i] = INF;
	const int CIRCULAR_QUE_SIZE = 10000;//max weight
	queue<int> circularQue[CIRCULAR_QUE_SIZE];
	int cirIndex=0;
	int nElements = 0;

	dist[source]=0;
	//que.insert(make_pair(0,source));
	circularQue[0].push(source);
	++nElements;
	
	while (nElements) {
		//int u = que.begin()->second;
		//int w = que.begin()->first;
		//if (cirIndex == 10) cirIndex = 0;
		while (circularQue[cirIndex].empty()) {
			++cirIndex;
			if (cirIndex == CIRCULAR_QUE_SIZE) cirIndex = 0;
		}
		int u = circularQue[cirIndex].front(); circularQue[cirIndex].pop();
		if (u == dest) return dist[dest];
		//int w = circularQue[cirIndex]
		//cerr <<"u " << u <<" is popped" << endl;

		//que.erase(que.begin());
		--nElements;
		
		for(auto &p:adj[u]) {
			int alt = dist[u] + p.first;
			int v = p.second;
			if (alt < dist[v]) {
				dist[v] = alt;
				//que.insert(make_pair(dist[v],v));
				int newIndex = cirIndex + p.first;
				if (newIndex>=CIRCULAR_QUE_SIZE) newIndex-=CIRCULAR_QUE_SIZE;

				circularQue[newIndex].push(v); 
				++nElements;
			}
		}
	}
	#ifdef DEBUG
	for(int i=0;i<=nRows*nCols;i++) {
		cerr <<"i " << i << " " << dist[i] << endl;
	}
	#endif
	return dist[dest];
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
		int maxWeight = 0;
		for(i=0;i<m;i++) {
			u = input.ReadNext();
			v = input.ReadNext();
			w = input.ReadNext();
			maxWeight = max(maxWeight,w);
			//edges[u][deg[u]++] = {w,v};

			//edges[v][deg[v]++] = {w,u};

			adj[u].push_back(make_pair(w,v));
			adj[v].push_back(make_pair(w,u));
		}
		//int ans = dijkstra(source,n,destination);//0.083
		//dijkstraCrazyQueue(source,n,destination,maxWeight); //0.228
		//SPFA_SLF(n,source,destination); //0.041
		int ans = dijkstraBidirectional(source,n,destination);
		/*
		output.PrintStr("Case #");
		output.PrintUint(numCase,':');
		output.PrintChar(' ');
		*/
		//cout << "Case #" << numCase <<": ";
		if(ans==INF) {
			//output.PrintStr("unreachable\n");
			printf("Case #%d: unreachable\n",numCase);
			//cout << "unreachable" << "\n";
		} else { 
			//output.PrintUint(dist[destination],'\n');
			printf("Case #%d: %d\n", numCase, ans);
			//cout << dist[destination] << "\n";
		}
	}
	//output.Flush();
	return 0;
}