#include <iostream>
using namespace std;

#include <cstring>
#include <cstdio>
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

const int SIZE = 100010;
int a[SIZE];

const int INF = 1000000000;


FastInput input;
int main() {
	int n, s;
	ios_base::sync_with_stdio(false);
	
	while (true) {
		n = input.ReadNext();
		if (n == 0x80000000) break;
		s = input.ReadNext();
		//cerr << "yes" << endl;
		for(int i=0;i<n;i++) {
			a[i] = input.ReadNext();
		}

		int minLen = INF;

		int start = 0;
		int i = start;

		long long sum = 0;
		{
			//cerr << "start " << start << endl;
			i=start;
			while (i<n) {
				sum += a[i];
				if (sum>=s) {
					int len = i-start+1;
					//cerr << "i " << i << " start " << start << " sum " << sum << endl;
					minLen = min(minLen,len);
					while (start <= i && sum-a[start]>=s) {
						sum -= a[start];
						start++;
						minLen = min(minLen,i-start+1);
						
					}
					//cerr << "After i " << i << " start " << start << " sum " << sum << " mLen " << minLen<< endl;
				}
				i++;
			}
		}	
		if (minLen != INF)	
			cout << minLen << "\n";
		else
			cout << "0\n";
	}
	return 0;
}