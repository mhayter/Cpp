#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <deque>
#include <list>
#include <forward_list>
#include <queue>
using namespace std;

#include <cstdio>
#include <cstring>
#include <cstdint>

//kind of right  but slow regardless 0.163 WA

// #2 0.122s macro + no forloop check
// #3 0.146s move constructor + save index 
// #3 0.153s dynamic graph construction
// now #5 0.215s -> 0.206s
// change initialization from fastest crazy queue
// no repeats visited = 0!

#define SLF
//#define LLL

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

const int INF = 1000000000;
const int SIZE = 1000*1000;

int nRows,nCols;
int Fdist[SIZE];
int Bdist[SIZE];

int grid[1010][1010];

const int CIRC_QUE_SIZE = 10;
deque<pair<int,pair<int,int> > > Fque[CIRC_QUE_SIZE];
deque<pair<int,pair<int,int> > > Bque[CIRC_QUE_SIZE];
bitset<SIZE>Fprocessed,Bprocessed;
int Felements, Belements;


const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};



int getIndex (int y,int x) {
	return y*nCols + x;
}

#define db(x) cerr << #x << " = " << x << endl;

int functionRelax(deque<pair<int,pair<int,int> > > QUE1[], deque<pair<int, pair<int,int> > > QUE2[], bitset<SIZE> &PROCESSED1, bitset<SIZE> &PROCESSED2, int DIST1[],int DIST2[], int U1, 
	int &minDist, int &que1Elements, int &que2Elements, int &que1Index, int &que2Index) {

	if (que1Elements) {
		int que1TopWeight=0, que2TopWeight=0;
		//find non empty bucket
		while (QUE1[que1Index].empty()) {
			++que1Index;
			if (que1Index == CIRC_QUE_SIZE) que1Index = 0;
		}
		
		pair<int, int > u = QUE1[que1Index].front().second; 
		//db(que1Elements);db(que2Elements);
		if (que2Elements) {
			//find nonEmptybucket
			while (QUE2[que2Index].empty()) {
				++que2Index;
				if (que2Index == CIRC_QUE_SIZE) que2Index = 0;
			} 
		}
		pair<int, int> other = QUE2[que2Index].front().second;

		que1TopWeight = QUE1[que1Index].front().first;
		que2TopWeight = QUE2[que2Index].front().first;

		//cerr <<"u = " << u.first << " " << u.second <<endl;
		//db(que2TopWeight);db(que1TopWeight);

		if (que2TopWeight+ que1TopWeight >= minDist) return minDist;
		QUE1[que1Index].pop_front();
		que1Elements--;

		int uIndex = getIndex(u.first,u.second);

		//////////////LOOOP THRU NEIGHBORS /////////////////
		int ny, nx;
		ny = u.first+1; nx = u.second;
		if (ny < nRows) {
			int w = grid[ny][nx];
			int alt = DIST1[uIndex] + w;
			if (alt < DIST1[getIndex(ny,nx)]) {
				//cerr << "down " << endl;
				DIST1[getIndex(ny,nx)] = alt;
				if (PROCESSED2[getIndex(ny,nx)]) {
					minDist = min(minDist, DIST1[uIndex] + DIST2[getIndex(ny,nx)]);
				}
				int newIndex = que1Index + w;
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;
				QUE1[newIndex].push_front(make_pair(alt,make_pair(ny,nx))); 
				++que1Elements;
			}
		}
		ny = u.first-1; nx= u.second;
		if (ny >= 0) {
			int w = grid[ny][nx];
			int alt = DIST1[uIndex] + w;
			if (alt < DIST1[getIndex(ny,nx)]) {
				//cerr << "up" << endl;
				DIST1[getIndex(ny,nx)] = alt;
				if (PROCESSED2[getIndex(ny,nx)]) {
					minDist = min(minDist, DIST1[uIndex] + DIST2[getIndex(ny,nx)]);
				}
				int newIndex = que1Index + w;
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;
				QUE1[newIndex].push_front(make_pair(alt,make_pair(ny,nx))); 
				++que1Elements;
			}
		}
		ny = u.first; nx = u.second+1;
		if (nx < nCols) {
			int w = grid[ny][nx];
			int alt = DIST1[uIndex] + w;
			if (alt < DIST1[getIndex(ny,nx)]) {
				//cerr << "right" << endl;
				DIST1[getIndex(ny,nx)] = alt;
				//cerr << "DIST1 = " << DIST1[getIndex(ny,nx)] << endl;
				if (PROCESSED2[getIndex(ny,nx)]) {
					minDist = min(minDist, DIST1[uIndex] + DIST2[getIndex(ny,nx)]);
				}
				int newIndex = que1Index + w;
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;
				QUE1[newIndex].push_front(make_pair(alt,make_pair(ny,nx))); 
				++que1Elements;
			}
		}
		ny = u.first; nx = u.second-1;
		if (nx>=0) {
			int w = grid[ny][nx];
			int alt = DIST1[uIndex] + w;
			if (alt < DIST1[getIndex(ny,nx)]) {
				//cerr << "left " << endl;
				DIST1[getIndex(ny,nx)] = alt;
				//cerr << "DIST1 " << DIST1[getIndex(ny,nx)] << endl;
				if (PROCESSED2[getIndex(ny,nx)]) {
					minDist = min(minDist, DIST1[uIndex] + DIST2[getIndex(ny,nx)]);
				}
				int newIndex = que1Index + w;
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;
				QUE1[newIndex].push_front(make_pair(alt,make_pair(ny,nx))); 
				++que1Elements;
			}
		}

		PROCESSED1[uIndex] = 1;
	}
	return -1;
}

int dijkstraCrazyQueueCreateNodes(pair<int,int> source, int n,pair<int,int> dest) {
	///////////////RESET///////////////////////////////////
	if (source == dest) return 0;
	for(int i=0;i<n;i++) {Fdist[i] = Bdist[i] = INF;}
	
	for(int i=0;i<CIRC_QUE_SIZE;i++) {
		Fque[i].clear();
		Bque[i].clear();
	}
	Fprocessed = Bprocessed = 0;
	Fdist[getIndex(source.first,source.second)]=0; Bdist[getIndex(dest.first,dest.second)]=0;

	for(int i=0;i<CIRC_QUE_SIZE;i++) {Fque[i].clear(); Bque[i].clear();}
	////////////////////////////////////////////////////////////

	/////////////INSERT ////////////////////////////////////////
	int FqueIndex = 0;
	int BqueIndex = 0;

	Fdist[0] = grid[0][0];
	Bdist[getIndex(dest.first,dest.second)] = grid[dest.first][dest.second];

	Fque[0].push_front(make_pair(0,source));
	Bque[0].push_front(make_pair(0,dest));
	Felements = Belements = 1;

	//////////////////END INSERT //////////////////////////////////

	int ans = INF;
	int minDist = INF;

	int Fu,Bu;
	int alt, v;

	while (Felements || Belements) {
		ans = functionRelax(Fque,Bque,Fprocessed,Bprocessed,Fdist,Bdist,Fu,minDist,Felements,Belements,FqueIndex,BqueIndex);
		if (ans != -1) return ans;
		ans = functionRelax(Bque,Fque,Bprocessed,Fprocessed,Bdist,Fdist,Bu,minDist,Belements,Felements,BqueIndex,FqueIndex);
		if (ans != -1) return ans;
	}

	return INF;
}

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#define fgets fgets_unlocked
#endif

int main() {
	FastInput input;

	int nCases = input.ReadNext();
	
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		//cerr << "************************* CASE # " << caseNum << endl;
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		int nNodes = 1;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = input.ReadNext();
			}
		}
		printf("%d\n", dijkstraCrazyQueueCreateNodes(make_pair(0,0), nRows*nCols, make_pair(nRows-1,nCols-1)));
	}
	//cout <<"fart" << endl;
	//output.Flush();
	return 0;
}