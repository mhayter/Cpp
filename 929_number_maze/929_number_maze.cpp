//#include <iostream>
#include <set>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <cstdint>
//Library stolen from codechef
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

const int SIZE = 1000*1000;

int nRows,nCols;
int grid[1010][1010];

vector<pair<int,int>>graph[SIZE];
int dist[SIZE];

int dijkstra(int source, int n,int dest) {
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
	#ifdef DEBUG
	for(int i=0;i<=nRows*nCols;i++) {
		cerr <<"i " << i << " " << dist[i] << endl;
	}
	#endif
	return dist[dest];
}

void buildGraph(int nNodes) {
	//int dy[]={1,0,-1,0};
	//int dx[]={0,1,0,-1};

	for(int i=0;i<nNodes;i++) graph[i].clear();
	//super node for begining
	graph[0].push_back(make_pair(grid[0][0],1));

	//generic connect
	for(int i=0;i<nRows;i++) {
		for(int j=0;j<nCols;j++) {
			int nodeVal = i*nCols+j+1;
			if (j-1>=0) // add it
				graph[nodeVal].push_back(make_pair(grid[i][j-1],nodeVal-1));
			if (j+1<nCols) 
				graph[nodeVal].push_back(make_pair(grid[i][j+1],nodeVal+1));
			if (i-1>=0)
				graph[nodeVal].push_back(make_pair(grid[i-1][j],nodeVal-nCols));
			if (i+1<nRows)
				graph[nodeVal].push_back(make_pair(grid[i+1][j],nodeVal+nCols));
		}
	}
	#ifdef DEBUG
	for(int i=0;i<=nRows*nCols;i++) {
		cerr << "i " << i << endl;
		for(int j=0;j<graph[i].size();j++) {
			cerr <<"  "<< graph[i][j].first << " " << graph[i][j].second << endl;
		}
		cerr << endl;
	}
	#endif
	
}


int main() {
	//ios_base::sync_with_stdio(false);

	FastInput input;
	FastOutput output;

	int nCases = input.ReadNext();
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();

		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = input.ReadNext();
			}
		}
		int nNodes = nRows*nCols+1;
		//build graph
		buildGraph(nNodes);
		output.PrintUint(dijkstra(0,nNodes, nRows*nCols),'\n');
	}
	output.Flush();
	return 0;
}