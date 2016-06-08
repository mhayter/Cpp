#include <bits/stdc++.h>
using namespace std;

class FastInput {
public:
FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
}
uint32_t readNextUnsigned() {
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

//0.040s fast input -- must need to reduced d*d
//0.930s unordered map clear
//0.040s with stdio(false)

struct Population {
	int y;
	int x;
	int size;
};

const int SIZE = 20010;
const int GRID_SIZE = 1030;
int grid[GRID_SIZE][GRID_SIZE];

int main() {

	FastInput input;
	ios_base::sync_with_stdio(false);

	int nCases = input.readNextUnsigned();// cin >> nCases;
	for(int caseNum = 1; caseNum <= nCases; caseNum++) {
		int d = input.readNextUnsigned();// cin >> d;
		int nPopulations = input.readNextUnsigned();// cin >> nPopulations;
		int bestSum = 0;
		int ansy = -1;
		int ansx = -1;
		int maxy = 0;
		int maxx = 0;
		int miny = GRID_SIZE;
		int minx = GRID_SIZE;
		for(int i=0;i<nPopulations;i++) {
			int y = input.readNextUnsigned();
			int x = input.readNextUnsigned();
			int size = input.readNextUnsigned();// cin >> y >> x >> size;
			maxy = max(maxy, y+d);
			maxx = max(maxx, x+d);

			miny = min(miny, y-d);
			minx = min(minx, x-d);

			int addyStart = -d+y;
			if (addyStart < 0) addyStart = -y;
			else addyStart = -d;
			int addxStart = -d+x;
			if (addxStart < 0) addxStart = -x;
			else addxStart = -d;

			for(int addy = addyStart; addy <= d ;addy++) {
				for(int addx = addxStart; addx <=d ;addx++) {
					int ny = addy+y;
					int nx = addx+x;
					//cerr << "ny " << ny << " nx " << nx << " " << grid[ny][nx]<< endl;
					if (ny<GRID_SIZE && nx < GRID_SIZE && ny>=0 && nx>=0) {
						grid[ny][nx] += size;
						if (grid[ny][nx] > bestSum) {
							bestSum = grid[ny][nx];
							ansx = nx;
							ansy = ny;
						} else if (grid[ny][nx] == bestSum) {
							if (ny < ansy) {
								ansy = ny;
								ansx = nx;
							}else if (ny == ansy && nx <ansx) {
								ansy = ny;
								ansx = nx;
							}
						}
					}
				}
			}
		}
		
		if (caseNum < nCases) {
			//cerr << miny << " " << maxy << " " << minx << " " << maxx << endl;
			for(int i=max(0,miny);i<=min(GRID_SIZE-1,maxy);i++) {
				for(int j=max(0,minx);j<=min(GRID_SIZE-1, maxx);j++){
					grid[i][j] = 0;
				}
			}
		}
		//cerr << "done" << endl;
		cout << ansy  << " " << ansx << " " << bestSum << "\n";

	}
	return 0;
}