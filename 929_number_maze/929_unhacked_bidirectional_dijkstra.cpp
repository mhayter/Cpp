#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <deque>
#include <list>
#include <forward_list>
#include <queue>
using namespace std;
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdint>
// 0.126s slower with last move added pairs
// #2 0.119s remove visited
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
		uint8_t m_buffer[32768*2];
		uint32_t m_data[16384*2];
		size_t m_dataOffset, m_dataSize;
		uint32_t m_v;
};

const int INF = 1000000000;
const int SIZE = 1000*1000;

int nRows,nCols;
int dist[SIZE];

int grid[1010][1010];

struct State {
	int ny;
	int nx;
};

const int CIRC_QUE_SIZE = 16;
const int CIRC_QUE_SIZE_MINUS_ONE = CIRC_QUE_SIZE - 1;
pair<int,int> circularQue[CIRC_QUE_SIZE][SIZE];// <y,x>,lastmove
int cqsize[CIRC_QUE_SIZE];

int cqs[CIRC_QUE_SIZE],cqe[CIRC_QUE_SIZE];
//bitset<SIZE>visitied;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int nProcessed;

namespace bidirectional_dijkstra {
	int Fdist[SIZE];
	int Bdist[SIZE];

	const int CIRC_QUE_SIZE = 10;
	deque<pair<int,pair<int,int> > > Fque[CIRC_QUE_SIZE];
	deque<pair<int,pair<int,int> > > Bque[CIRC_QUE_SIZE];
	//bitset<SIZE>Fprocessed,Bprocessed;
	int Felements, Belements;


	const int dy[] = {1,0,-1,0};
	const int dx[] = {0,1,0,-1};



	int getIndex (int y,int x) {
		return y*nCols + x;
	}

	#define db(x) cerr << #x << " = " << x << endl;
	#define UPDATE(QUE1, DIST1, DIST2, minDist, que1Elements, que1Index)\
			int w = grid[ny][nx];\
			int alt = DIST1[uIndex] + w;\
			if (alt < DIST1[nI]) {\
				DIST1[nI] = alt;\
				minDist = min(minDist, DIST1[uIndex] + DIST2[nI]);\
				int newIndex = que1Index + w;\
				if (newIndex>=CIRC_QUE_SIZE) newIndex-=CIRC_QUE_SIZE;\
				QUE1[newIndex].push_front(make_pair(alt,make_pair(ny,nx))); \
				++que1Elements;\
			}

	#define RELAX(QUE1, QUE2, DIST1, DIST2, U1, minDist, que1Elements, que2Elements, que1Index, que2Index) \
		{\
			pair<int, int > u = move(QUE1[que1Index].front().second);\
			int que1TopWeight = QUE1[que1Index].front().first;\
			int que2TopWeight = QUE2[que2Index].front().first;\
			if (que2TopWeight+ que1TopWeight >= minDist) return minDist;\
			QUE1[que1Index].pop_front();\
			que1Elements--;\
			nProcessed++;\
			int uIndex = getIndex(u.first,u.second);\
			int ny, nx;\
			int nI;\
			ny = u.first+1; nx = u.second;\
			if (ny < nRows) {\
				nI = uIndex + nCols;\
				UPDATE(QUE1, DIST1, DIST2, minDist, que1Elements, que1Index);\
			}\
			ny = u.first-1; nx= u.second;\
			if (ny >= 0) {\
				nI = uIndex - nCols;\
				UPDATE(QUE1, DIST1, DIST2, minDist, que1Elements, que1Index);\
			}\
			ny = u.first; nx = u.second+1;\
			if (nx < nCols) {\
				nI = uIndex + 1;\
				UPDATE(QUE1, DIST1, DIST2, minDist, que1Elements, que1Index);\
			}\
			ny = u.first; nx = u.second-1;\
			if (nx>=0) {\
				nI = uIndex - 1;\
				UPDATE(QUE1, DIST1, DIST2, minDist, que1Elements, que1Index);\
			}\
			while (QUE1[que1Index].empty()) {\
				++que1Index;\
				if (que1Index == CIRC_QUE_SIZE) que1Index = 0;\
			}\
		}\


	int functionRelax(deque<pair<int,pair<int,int> > > QUE1[], deque<pair<int, pair<int,int> > > QUE2[], bitset<SIZE> &PROCESSED1, bitset<SIZE> &PROCESSED2, int DIST1[],int DIST2[], int U1, 
		int &minDist, int &que1Elements, int &que2Elements, int &que1Index, int &que2Index) {

		if (que1Elements) {
			int que1TopWeight=0, que2TopWeight=0;
			//find non empty bucket
			while (QUE1[que1Index].empty()) {
				++que1Index;
				if (que1Index == CIRC_QUE_SIZE) que1Index = 0;
			}
			//nProcessed++;
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

			if (que2TopWeight+ que1TopWeight >= minDist+2) {
				//cout <<"Weights on ques " << que2TopWeight << " " << que1TopWeight << " mindis " << minDist << endl;
			 	return minDist;
			 }
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
						minDist = min(minDist,DIST1[uIndex] + DIST2[getIndex(ny,nx)]);
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

	int bidirectionalDijkstraCrazyQueueCreateNodes(pair<int,int> source, int n,pair<int,int> dest) {
		///////////////RESET///////////////////////////////////
		if (source == dest) return grid[source.first][source.second];
		int start = clock();
		for(int i=0;i<n;i++) {Fdist[i] = Bdist[i] = INF;}
		
		for(int i=0;i<CIRC_QUE_SIZE;i++) {
			Fque[i].clear();
			Bque[i].clear();
		}
		//Fprocessed = Bprocessed = 0;

		for(int i=0;i<CIRC_QUE_SIZE;i++) {Fque[i].clear(); Bque[i].clear();}
		////////////////////////////////////////////////////////////

		/////////////INSERT ////////////////////////////////////////
		int FqueIndex = 0;
		int BqueIndex = 0;

		Fdist[0] = grid[0][0];
		Bdist[getIndex(dest.first,dest.second)] = grid[dest.first][dest.second];

		Fque[0].push_front(make_pair(grid[0][0],source));
		Bque[0].push_front(make_pair(grid[dest.first][dest.second],dest));
		Felements = Belements = 1;
		cerr << "INIt " <<  clock() - start << endl;
		//////////////////END INSERT //////////////////////////////////

		int ans = INF;
		int minDist = INF;

		int Fu,Bu;
		int alt, v;

		//nProcessed = 0;
		while (Felements || Belements) {
			for(int k=0;k< 10000;k++) {
				RELAX(Fque,Bque,Fdist,Bdist,Fu,minDist,Felements,Belements,FqueIndex,BqueIndex);
			}
			for(int k=0;k < 10000;k++) {
				RELAX(Bque,Fque,Bdist,Fdist,Bu,minDist,Belements,Felements,BqueIndex,FqueIndex);
			}
		}

		return INF;
	}
}

#define DOIT(direction)\
	int w = grid[ny][nx];\
	int alt = dist[uIndex] + w;\
	if (alt < dist[getIndex(ny,nx)]) {\
		dist[getIndex(ny,nx)] = alt;\
		int newIndex = (cirIndex + w) & CIRC_QUE_SIZE_MINUS_ONE;\
		circularQue[newIndex][cqsize[newIndex]++] = make_pair(ny,nx); \
		++nElements;\
	}\

int getIndex (int y,int x) {
	return y*nCols + x;
}
enum DIR {UP,DOWN,LEFT,RIGHT};

#define DO_UP\
	ny = u.first-1; nx= u.second;\
	if (ny >= 0) {\
		DOIT(UP);\
	}

#define DO_DOWN\
	ny = u.first+1; nx = u.second;\
	if (ny < nRows) {\
		DOIT(DOWN);\
	}

#define DO_LEFT\
	ny = u.first; nx = u.second-1;\
	if (nx>=0) {\
		DOIT(LEFT);\
	}

#define DO_RIGHT\
	ny = u.first; nx = u.second+1;\
	if (nx < nCols) {\
		DOIT(RIGHT);\
	}




int dijkstraCrazyQueueCreateNodes(pair<int,int> source, int n,pair<int,int> dest) {
	for(int i=0;i<n;i++){ dist[i] = INF; }
	//visitied = 0;
	for(int i=0;i<CIRC_QUE_SIZE;i++) {
		cqs[i] = cqe[i] = 0;
		cqsize[i] = 0;
	}
	int cirIndex=0;
	int nElements = 0;

	dist[0]=grid[0][0];
	circularQue[0][cqsize[0]++]= make_pair(source.first,source.second); //START RIGHT OR DOWN
	++nElements;
	
	while (nElements) {
		for(int i=0;i<cqsize[cirIndex];i++) {
			pair<int,int> u = circularQue[cirIndex][i];//pop front
			//cerr << "u " << u.first << " " << u.second << endl;
			if (u.first == dest.first && u.second == dest.second) return dist[getIndex(dest.first,dest.second)];
			int uIndex = getIndex(u.first,u.second);
			--nElements;
			++nProcessed;

			int ny, nx;
			DO_RIGHT;
			DO_DOWN;
			DO_LEFT;
			DO_UP
		}
		
		cqsize[cirIndex] = 0;
		++cirIndex;
		cirIndex &= CIRC_QUE_SIZE_MINUS_ONE;
	}
	return dist[getIndex(dest.first,dest.second)];
}

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#define fgets fgets_unlocked
#endif

int main() {
	//int start = clock();
	ios_base::sync_with_stdio(false);
	FastInput input;
	int nCases = input.ReadNext();

	int nTimes = 0;
	
	for(int caseNum=1;caseNum<=nCases;caseNum++) {
		nRows = input.ReadNext();
		nCols = input.ReadNext();
		int nNodes = 1;
		for(int i=0;i<nRows;i++) {
			for(int j=0;j<nCols;j++) {
				grid[i][j] = input.ReadNext();
			}
		}
		nProcessed = 0;
		//cerr << clock() -start << endl;
		if (false)
			cout << dijkstraCrazyQueueCreateNodes(make_pair(0,0), nRows*nCols, make_pair(nRows-1,nCols-1)) << "\n";
		else {
			//nTimes++;
			cout << bidirectional_dijkstra::bidirectionalDijkstraCrazyQueueCreateNodes(make_pair(0,0), nRows*nCols, make_pair(nRows-1,nCols-1)) << "\n";
			
			//if (nTimes >= 5) throw -1;
		}
		cerr << "nProcessed " <<  nProcessed << endl;
	}
	//cout <<grid[0][0] << endl;
	//output.Flush();
	return 0;
}