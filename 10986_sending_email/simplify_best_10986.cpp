
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <set>
using namespace std;

//funciton replacement makes it 0.018s 12/16/2015??? now 0.019

//certified #1 7/26/2015 0.036  0.019s 8/12/2015 resubit
//only works on bidirectional for now reverse follow edges latter
//http://www.cs.princeton.edu/courses/archive/spr06/cos423/Handouts/EPP%20shortest%20path%20algorithms.pdf

class FastInput {
	public:
	FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
	}
	uint32_t ReadNext() {
		if (m_dataOffset == m_dataSize) {
			int r = fread_unlocked(m_buffer,1,sizeof(m_buffer),stdin);
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

//w,v
vector<pair<int,int>> adj[SIZE];

struct Edge {
	int w;
	int v;
};


int Fdist[SIZE];
int Bdist[SIZE];
bitset<SIZE> Fprocessed,Bprocessed;

struct Heap {
	const static int HEAP_SIZE = 50010*2;
	pair<int,int> heap[HEAP_SIZE];
	int hpsize=0;
	int min, minInd, left, right,place;
	#define LEFT(x) (2*(x)+1)
	#define RIGHT(x) (2*(x)+2)
	#define PARENT(x) (((x)-1)/2)

	void reset() {
		hpsize = 0;
	}
	int size() {
		return hpsize;
	}
	pair<int,int> top() {
		return heap[0];
	}
	void insert(const pair<int,int> a) {
		//min head parent < place
		place = hpsize;

		while (place && heap[PARENT(place)]>a) {
			heap[place] = heap[PARENT(place)];
			place = PARENT(place);
		}
		heap[place] = a;
		++hpsize;
	}
	int secondExtract() {
		int ans = heap[0].second;
		heap[0] = move(heap[--hpsize]);
		place = 0;
		while (true) {
			minInd = place;
			left = LEFT(place);
			right = RIGHT(place);

			if (left < hpsize && heap[minInd].first > heap[left].first){
				minInd = left;
			} //bad
			if (right < hpsize && this->min > heap[right].first){
				minInd = right;
			}
			if (minInd != place) {
				swap(heap[place],heap[minInd]);
				place = minInd;
			} else break;
		}
		return ans;
	}
	
	pair<int,int> extract() {
		pair<int,int> ans = move(heap[0]);
		heap[0] = move(heap[--hpsize]);
		place = 0;
		while (true) {
			this->min = heap[place].first;
			minInd = place;
			left = LEFT(place);
			right = RIGHT(place);

			if (left < hpsize && this->min > heap[left].first){
				minInd = left;
				this->min = heap[minInd].first;
			} //bad
			if (right < hpsize && this->min > heap[right].first){
				minInd = right;
				this->min = heap[minInd].first;
			}
			if (minInd != place) {
				swap(heap[place],heap[minInd]);
				place = minInd;
			} else break;
		}
		return ans;
	}
};

Heap Fque,Bque;

#define RELAX(QUE1,QUE2,PROCESSED1,PROCESSED2,DIST1,DIST2,U1) {\
	if (QUE1.size()) {\
		if (QUE2.top().first + QUE1.top().first >= minDist) return minDist;\
		U1 = QUE1.extract().second;\
		for(auto &p:adj[U1]) {\
			alt = DIST1[U1] + p.first;\
			v = p.second;\
			if (alt < DIST1[v]) {\
				DIST1[v] = alt;\
				if (PROCESSED2[v]) {\
					minDist = min(minDist,DIST1[U1]+DIST2[v]+p.first);\
				}\
				QUE1.insert(make_pair(alt,v));\
			}\
		}\
		PROCESSED1[U1] = 1;\
	}\
}

int functionRelax(Heap &QUE1, Heap &QUE2, bitset<SIZE> &PROCESSED1, bitset<SIZE> &PROCESSED2, int DIST1[],int DIST2[], int U1, int &minDist) {
	if (QUE1.size()) {
		if (QUE2.top().first + QUE1.top().first >= minDist) return minDist;
		U1 = QUE1.extract().second;
		for(auto &p:adj[U1]) {
			int alt = DIST1[U1] + p.first;
			int v = p.second;
			if (alt < DIST1[v]) {
				DIST1[v] = alt;
				if (PROCESSED2[v]) {
					minDist = min(minDist,DIST1[U1]+DIST2[v]+p.first);
				}
				QUE1.insert(make_pair(alt,v));
			}
		}
		PROCESSED1[U1] = 1;
	}
	return -1;
}

int dijkstraBidirectional(int source, int n,int dest) {
	if (source == dest) return 0;
	for(int i=0;i<n;i++) {Fdist[i] = Bdist[i] = INF;}
	
	Fque.reset();
	Bque.reset();
	Fprocessed = Bprocessed = 0;
	Fdist[source]=0; Bdist[dest]=0;
	
	Fque.insert(make_pair(0,source));
	Bque.insert(make_pair(0,dest));

	int minDist = INF;

	int Fu,Bu;
	int alt, v;

	int ans = INF;
	while (Fque.size() || Bque.size()) {
		//RELAX(Fque,Bque,Fprocessed,Bprocessed,Fdist,Bdist,Fu);
		//RELAX(Bque,Fque,Bprocessed,Fprocessed,Bdist,Fdist,Bu);

		ans = functionRelax(Fque,Bque,Fprocessed,Bprocessed,Fdist,Bdist,Fu,minDist);
		if (ans != -1) return ans;
		ans = functionRelax(Bque,Fque,Bprocessed,Fprocessed,Bdist,Fdist,Bu,minDist);
		if (ans != -1) return ans;
	}
	return INF;
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
		
		for(i=0;i<m;i++) {
			u = input.ReadNext();
			v = input.ReadNext();
			w = input.ReadNext();

			adj[u].emplace_back(make_pair(w,v));
			adj[v].emplace_back(make_pair(w,u));
		}
		int ans = dijkstraBidirectional(source,n,destination);//0.036
		if(ans==INF) {
			printf("Case #%d: unreachable\n",numCase);
		} else { 
			printf("Case #%d: %d\n", numCase, ans);
		}
	}
	//output.Flush();
	return 0;
}