#include <bits/stdc++.h>
using namespace std;

//tied for 1st 0.010s 5/11/2016

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

const int SIZE = 110;
int grid[SIZE][SIZE];
int memo[SIZE][SIZE];
int n,k;
int maxFactor;

int dy[] = {1,0,-1,0};
int dx[] = {0,-1,0, 1};

bool isValid(int y,int x,int lastUsedValue) {
	return (y>=0 && x>=0 && y<n && x<n && grid[y][x] >lastUsedValue);
}

int hop(int y,int x, int lastUsedValue) {
	if (memo[y][x] != -1) return memo[y][x];
	int ans = 0;
	for(int factor = 1; factor<= maxFactor;factor++){
		for(int i=0;i<4;i++) {
			int ny = y + factor*dy[i];
			int nx = x + factor*dx[i];
			if (isValid(ny,nx, lastUsedValue)) {
				ans = max(ans,hop(ny,nx,grid[ny][nx])+grid[ny][nx]);
			}
		}
	}
	return memo[y][x] = ans;
}


//Stupidly optimized to reduce unnessary checks
int unrolledHop(int y,int x, int lastUsedValue) {
	if (memo[y][x] != -1) return memo[y][x];
	int ans = 0;
	for(int factor = 1; factor<= maxFactor;factor++){
		int ny = y+factor;
		if (ny <n &&  grid[ny][x] >lastUsedValue)
			ans = max(ans,unrolledHop(ny,x,grid[ny][x])+grid[ny][x]);
		ny = y - factor;
		if (ny >= 0 &&  grid[ny][x] >lastUsedValue)
			ans = max(ans,unrolledHop(ny,x,grid[ny][x])+grid[ny][x]);
		int nx = x + factor;
		if (nx <n &&  grid[y][nx] >lastUsedValue) 
			ans = max(ans,unrolledHop(y,nx,grid[y][nx])+grid[y][nx]);
		nx = x - factor;
		if (nx >=0 &&  grid[y][nx] >lastUsedValue)
			ans = max(ans,unrolledHop(y,nx,grid[y][nx])+grid[y][nx]);
	}
	return memo[y][x] = ans;
}

int main() {
	FastInput input;
	int nCases = input.readNextUnsigned();
	for(int caseNum = 1; caseNum<=nCases;caseNum++) {
		n = input.readNextUnsigned();
		k = input.readNextUnsigned();
		maxFactor = min (n,k);
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				grid[i][j] = input.readNextUnsigned();
				memo[i][j] = -1;
			}
		}

		printf("%d\n",unrolledHop(0,0,grid[0][0])+grid[0][0]);
		if (caseNum == nCases) break;
		printf("\n");
	}
	return 0;
}