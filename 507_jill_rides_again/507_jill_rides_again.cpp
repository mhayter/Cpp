#include <bits/stdc++.h>
using namespace std;

//0.000s codeforces io readInt()!
//From 0.180s -> 0.050s sync_with_stdio(false);


class FastInput {
public:
FastInput() {
	m_dataOffset = 0;
	m_dataSize = 0;
	m_v = 0x80000000;
}
int32_t readInt() {
	if (m_dataOffset == m_dataSize) {
		int r = fread(m_buffer,1,sizeof(m_buffer),stdin);
		if (r <= 0) return m_v;
		m_dataOffset = 0;
		m_dataSize = 0;
		int i = 0;
		if (m_buffer[0] < '0') {
			if (m_v != 0x80000000) {
				m_data[m_dataSize++] = (neg)? -m_v: m_v;
				m_v = 0x80000000;
			}
			for (; (i < r) && (m_buffer[i] < '-'); ++i);
		}
		//check for negative
		neg = false;
		 //bad
		for (; i < r;) {
			if (m_buffer[i] == '-') {neg = true;++i;}

			while (i < r && m_buffer[i] >= '0') {
				m_v = m_v * 10 + m_buffer[i] - 48;
				++i;
			} 
			if (m_buffer[i] <'0') {
				m_data[m_dataSize++] = (neg)? -m_v:m_v;
				neg = false;
				m_v = 0x80000000;
				for (i = i + 1; (i < r) && (m_buffer[i] < '-'); ++i);
			}
		}
	}
	return m_data[m_dataOffset++];
}
public:
	uint8_t m_buffer[32768];
	int32_t m_data[16384];
	size_t m_dataOffset, m_dataSize;
	int32_t m_v;
	bool neg;
};

const int SIZE = 20010;
int a[SIZE];

//FastInput input;

namespace CodeForcesIO {
	static char stdinBuffer[1024];
	static char* stdinDataEnd = stdinBuffer + sizeof (stdinBuffer);
	static const char* stdinPos = stdinDataEnd;

	void readAhead(size_t amount)
	{
	    size_t remaining = stdinDataEnd - stdinPos;
	    if (remaining < amount) {
	       memmove(stdinBuffer, stdinPos, remaining);
	       size_t sz = fread(stdinBuffer + remaining, 1, sizeof (stdinBuffer) - remaining, stdin);
	       stdinPos = stdinBuffer;
	       stdinDataEnd = stdinBuffer + remaining + sz;
	       if (stdinDataEnd != stdinBuffer + sizeof (stdinBuffer))
	         *stdinDataEnd = 0;
	    }
	}

	int readInt()
	{
	    readAhead(16);

	    int x = 0;
	    bool neg = false;
	    while (*stdinPos <'-') ++stdinPos;

	    if (*stdinPos == '-') {
	       ++stdinPos;
	       neg = true;
	    }

	    while (*stdinPos >= '0' && *stdinPos <= '9') {
	       x *= 10;
	       x += *stdinPos - '0';
	       ++stdinPos;
	    }


	    return neg ? -x : x;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	int nRoutes = CodeForcesIO::readInt();
	for(int i=0;i<nRoutes;i++) {
		int nStops = CodeForcesIO::readInt();
		for(int j=0;j+1<nStops;j++) {
			a[j] = CodeForcesIO::readInt();
			//cerr << a[j] << " " ;
		}
		//cerr << endl;
		int place = 0;
		int sum = 0; // ll ?
		int start = 0;
		int stop = 0;
		int maxStart = 0;
		int maxStop = 0;
		int maxDist = 0;
		int maxSum = 0;
		while (place +1 < nStops) {
			if(sum + a[place] >= 0){
				sum += a[place];
				//cerr << "place " << place << " a " << a[place] << " sum " << sum << endl;
				if (sum > maxSum) {
					maxSum = sum;
					stop = place;
					maxStart = start;
					maxStop = stop;
					maxDist = maxStop - maxStart;
				} else if (sum == maxSum) {
					stop = place;
					if (stop - start> maxDist) {
						maxDist = stop-start;
						maxStart = start;
						maxStop = stop;
					}
				}
			} else {
				start = stop = place+1;
				sum = 0;
			}
			place++;
		}
		if (maxSum > 0)
			cout << "The nicest part of route " << i+1 << " is between stops " << maxStart+1 << " and " << maxStop+2 << "\n";
		else {
			cout << "Route " << i+1 << " has no nice parts\n";
		}

	}
	return 0;
}