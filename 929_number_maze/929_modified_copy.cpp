// Time: 0.995s
// After fast input : 0.665s
// make pair no diff
// early break : 0.458s

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

 
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
 
#define INF 1e9
 
const int adjR[4] = {-1,  0, 1, 0};
const int adjC[4] = { 0, -1, 0, 1};
 
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
 

const int SIZE = 1000;
int weight[SIZE][SIZE];
int row, col, r, c, i, d, newr, newc;
 
int dijkstra() {
    priority_queue<iii,vector<iii>,greater<iii> > pq;
    vector<vi> dist;
 
    dist.clear();
    vi rowInit(col,INF);
    dist.assign(row,rowInit);
 
    //source dist
    dist[0][0] = weight[0][0];
 
    pq.push( iii( dist[0][0], ii(0,0) ) );
 
    while(!pq.empty()) {
        iii u = pq.top();
        pq.pop();
        r = u.second.first;
        c = u.second.second;
        d = u.first;

        if (r+1 == row && c+1 ==col) return dist[r][c];
        for(i=0;i<4;i++) {
            newr = r + adjR[i];
            newc= c + adjC[i];
 
            if(newr >= 0 && newr < row && newc >= 0 && newc < col) {
                if(d + weight[newr][newc] < dist[newr][newc]) {
                     dist[newr][newc] = d + weight[newr][newc];
                     pq.push( make_pair(dist[newr][newc], make_pair(newr,newc) ) );
                }
            }
        }
    }
 
    return dist[row-1][col-1];
}
 
int main(){
    int testcase, w;
    FastInput input;

    testcase = input.ReadNext();
 
    while(testcase--) {
        row = input.ReadNext();
        col = input.ReadNext();
 
        for(r=0; r<row; r++)
            for(c=0; c<col; c++) 
                weight[r][c] = input.ReadNext();
        printf("%d\n",    dijkstra());
    }
    return 0;
}
  