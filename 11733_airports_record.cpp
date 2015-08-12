#include<stdio.h>
#include<vector>
#include<algorithm>
#define sz 10001
using namespace std;

//cert #1 8/6/2015 0.036 
//props to http://mmrsiyam.blogspot.com/2014/11/uva-11733-airportscpp.html
//my OOP solution has a strange bug plus it probably should be OOP for speed
//the terrible style is not mine

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
        uint8_t m_buffer[32768*2];
        uint32_t m_data[16384*2];
        size_t m_dataOffset, m_dataSize;
        uint32_t m_v;
};

struct edge {
    int f,t,c;
    edge(int a,int b,int co) :
        f(a),t(b), c(co)
    {}
    friend bool operator<(const edge &a, const edge &b);
};

bool operator<(const edge &a, const edge &b) {
    return a.c < b.c;
}

int n,e,ac;

int par[sz];
int Rank[sz];

int set_find(int a) {
    if(a==par[a])
        return a;
    return(par[a]=set_find(par[a]));
}
void link(int x,int y) {
    if (Rank[x] < Rank[y]) {
        par[x] = y;
    } else if (Rank[y] < Rank[x]) {
        par[y] = x;
    } else {
        par[y] = x;
        Rank[x]++;
    }
}
void ini() {
    for(int i=0; i<=n; i++) {
        par[i]=i;
        Rank[i] = 0;
    }
}

const int MAX_WEIGHT = 10010;
vector<pair<int,int>> edgesCounting[MAX_WEIGHT];

int main() {
    int tst,t,i,j,f,k,c,ansi,cnt,cs;
    //scanf("%d",&tst);
    FastInput input;
    tst = input.readNextUnsigned();
    for(cs=1; cs<=tst; cs++) {
        n = input.readNextUnsigned();
        e = input.readNextUnsigned();
        ac = input.readNextUnsigned();
        ini();
        int myMaxWeight = 0;
        for(j=0; j<e; j++) {
            f = input.readNextUnsigned();
            t = input.readNextUnsigned();
            c = input.readNextUnsigned();

            if (c < ac) {
                //linear sort
                edgesCounting[c].push_back(make_pair(f,t));
                myMaxWeight = max(myMaxWeight,c);
            }
        }
        //linear sort extraction
        int weightTotal = 0;
        for(int weight = 1; weight<=myMaxWeight;++weight) {
            for(int j=0;j<edgesCounting[weight].size();++j) {
                int xroot = set_find(edgesCounting[weight][j].first);
                int yroot = set_find(edgesCounting[weight][j].second);
                if (xroot != yroot) {
                    link(xroot,yroot);
                    weightTotal += weight;
                }
            }
            edgesCounting[weight].clear();
        }

        ansi=weightTotal;
        cnt=0;
        for(i=1; i<=n; i++)
            if(par[i]==i)cnt++;

        printf("Case #%d: %d %d\n",cs,ansi+(cnt*ac),cnt);
    }
    return 0;
}